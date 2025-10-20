#ifndef LOADSERVICE_H
#define LOADSERVICE_H

#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QVersionNumber>

class LoadService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString statusMessage READ GetStatusMessage NOTIFY statusMessageChanged)

public:
    explicit LoadService(QObject *parent = nullptr) : QObject(parent) {
        m_exeDir = QCoreApplication::applicationDirPath();//路径拼接
        InitDatabase();
    }

    Q_INVOKABLE void readDatabaseConfig() {
        m_statusMessage = "正在读取数据库配置...";
        emit statusMessageChanged();

        // 检查数据库是否打开
        if (!m_db.isOpen()) {
            m_statusMessage = "错误：数据库连接失败";
            emit statusMessageChanged();
            return;
        }

        // 查询仅有的两个版本号字段（id=1）
        QSqlQuery query(m_db);
        if (!query.exec("SELECT newfile_version, oldfile_version FROM software_config WHERE id = 1")) {
            m_statusMessage = "错误：数据库查询失败";
            emit statusMessageChanged();
            return;
        }

        if (query.next()) {
            // 读取新版本号和旧版本号（处理空值）
            QVariant newVerVar = query.value("newfile_version");
            m_newVersion = newVerVar.isValid() && !newVerVar.isNull() ? newVerVar.toString() : "";

            QVariant oldVerVar = query.value("oldfile_version");
            m_oldVersion = oldVerVar.isValid() && !oldVerVar.isNull() ? oldVerVar.toString() : "";

            // 对比版本号，选择最高版本 + 拼接对应路径
            if (CompareVersions(m_oldVersion, m_newVersion) > 0) {
                m_highestVersion = m_oldVersion;
                m_highestVersionPath = QString("%1/software/%2/VLMUInsight.exe").arg(m_exeDir).arg(m_highestVersion);
                m_statusMessage = "选择旧版本: " + m_oldVersion;
            } else {
                m_highestVersion = m_newVersion;
                m_highestVersionPath = QString("%1/software/%2/VLMUInsight.exe").arg(m_exeDir).arg(m_highestVersion);
                // 新增：拼接旧版本路径（用于后续启动失败时 fallback）
                m_oldVersionPath = QString("%1/software/%2/VLMUInsight.exe").arg(m_exeDir).arg(m_oldVersion);
                m_statusMessage = "选择新版本: " + m_newVersion;
            }

        } else {
            m_statusMessage = "错误：数据库无配置数据";
            m_highestVersion = "";
            m_highestVersionPath = "";
            m_oldVersionPath = "";
        }
        emit statusMessageChanged();
    }

    // 核心修改：启动失败时自动重试旧版本路径
    Q_INVOKABLE void launchProgram() {
        // 1. 先尝试启动最高版本
        if (!m_highestVersionPath.isEmpty()) {
            QFileInfo highestFile(m_highestVersionPath);
            m_statusMessage = "正在启动最高版本: " + highestFile.fileName() + "（" + m_highestVersion + "）";
            emit statusMessageChanged();

            if (highestFile.exists()) {
                // 启动最高版本
                if (QProcess::startDetached(m_highestVersionPath)) {
                    m_statusMessage = "最高版本启动成功: " + highestFile.fileName();
                    emit statusMessageChanged();
                    return; // 启动成功，直接返回
                } else {
                    m_statusMessage = "最高版本启动失败，尝试启动旧版本...";
                    emit statusMessageChanged();
                }
            } else {
                m_statusMessage = "最高版本文件不存在，尝试启动旧版本...";
                emit statusMessageChanged();
            }
        } else {
            m_statusMessage = "最高版本路径为空，尝试启动旧版本...";
            emit statusMessageChanged();
        }

        // 2. 最高版本启动失败，重试旧版本路径
        if (!m_oldVersionPath.isEmpty()) {
            QFileInfo oldFile(m_oldVersionPath);
            if (oldFile.exists()) {
                m_statusMessage = "正在启动旧版本: " + oldFile.fileName() + "（" + m_oldVersion + "）";
                emit statusMessageChanged();

                if (QProcess::startDetached(m_oldVersionPath)) {
                    m_statusMessage = "旧版本启动成功: " + oldFile.fileName();
                } else {
                    m_statusMessage = "错误：旧版本启动也失败";
                }
            } else {
                m_statusMessage = "错误：旧版本文件也不存在";
            }
        } else {
            m_statusMessage = "错误：旧版本路径为空，无可用启动路径";
        }
        emit statusMessageChanged();
    }

    Q_INVOKABLE QString geadDatabaseConfig() { return m_highestVersionPath; }
    Q_INVOKABLE QString getHighestVersion() { return m_highestVersion; }
    Q_INVOKABLE QString GetStatusMessage() const { return m_statusMessage; }

signals:
    void statusMessageChanged();

private:
    void InitDatabase() {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        QString v_db_path = QCoreApplication::applicationDirPath() + "/bin/launch.db";
        m_db.setDatabaseName(v_db_path);

        // 新增：自动创建bin文件夹（避免路径不存在导致数据库打开失败）
        QDir binDir(QCoreApplication::applicationDirPath() + "/bin");
        if (!binDir.exists()) binDir.mkpath(".");

        if (m_db.open()) {
        } else {
            m_statusMessage = "数据库打开失败：" + m_db.lastError().text();
            emit statusMessageChanged();
        }
    }

    int CompareVersions(const QString &v1, const QString &v2) {
        QVersionNumber version1 = QVersionNumber::fromString(v1);
        QVersionNumber version2 = QVersionNumber::fromString(v2);
        if (version1 > version2) return 1;
        if (version1 < version2) return -1;
        return 0;
    }

private:
    QString m_exeDir;               // exe所在目录
    QString m_highestVersionPath;   // 最高版本路径
    QString m_oldVersionPath;       // 新增：旧版本路径（用于 fallback）
    QString m_highestVersion;       // 最高版本号
    QString m_newVersion;           // 数据库新版本号
    QString m_oldVersion;           // 数据库旧版本号
    QString m_statusMessage;        // 状态信息
    QSqlDatabase m_db;              // 数据库连接对象
};

#endif // LOADSERVICE_H
