#ifndef LOADSERVICE_H
#define LOADSERVICE_H

#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QProcess>
#include <QString>
#include <QSharedPointer>

#include "configure.h"

class LoadService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString statusMessage READ getStatusMessage NOTIFY statusMessageChanged)

public:
    explicit LoadService();

    Q_INVOKABLE bool initService();//暴露给QML使用
    Q_INVOKABLE bool launchProgram();//暴露给QML使用
    Q_INVOKABLE bool getCfgPath();//暴露给QML使用
    Q_INVOKABLE QString getStatusMessage();//暴露给QML使用

signals:
    void statusMessageChanged();

private:
    QSharedPointer<Configure> g_configure;
    QString m_new_version_path;
    QString m_old_version_path;
    QString m_new_version;
    QString m_old_version;
    QString m_statusMessage;//状态信息
    bool m_cfg_flag;
};

#endif // LOADSERVICE_H
