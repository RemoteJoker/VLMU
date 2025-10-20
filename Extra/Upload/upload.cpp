#include "upload.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QEventLoop>
#include <QUrl>

Upload::Upload() : m_port(21)
{
}

void Upload::SetServer(const QString& host, quint16 port)
{
    m_host = host;
    m_port = port;
}

bool Upload::CheckUpdate(const QString& remotePath, const QString &v_version)
{
    m_lastError.clear();
    if (m_host.isEmpty()) {
        m_lastError = "Host not set";
        return false;
    }
    if (remotePath.isEmpty()) {
        m_lastError = "Remote INI path is empty";
        return false;
    }
    QUrl url;
    url.setScheme("ftp");
    url.setHost(m_host);
    url.setPort(m_port);
    url.setPath(remotePath);
    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QByteArray iniData; // 用于暂存下载的INI内容
    bool downloadSuccess = false;
    QNetworkReply* reply = manager.get(QNetworkRequest(url));
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            iniData = reply->readAll(); // 读取INI文件内容到内存
            downloadSuccess = true;
        } else {
            m_lastError = "Download failed: " + reply->errorString();
        }
        eventLoop.quit();
    });
    eventLoop.exec(); // 阻塞等待下载完成
    reply->deleteLater();
    if (!downloadSuccess) {
        return false; // 下载失败直接返回
    }
    QSettings iniSettings;
    iniSettings.setIniCodec("UTF-8");
    QString remoteVersion = iniSettings.value("version").toString().trimmed();
    if (remoteVersion.isEmpty()) {
        m_lastError = "version field not found in INI";
        return false;
    }
    if(v_version == remoteVersion){
        return false;
    }
    return true;
}

bool Upload::Download(const QString& remotePath, const QString& localPath)
{
    m_lastError.clear();

    if (m_host.isEmpty()) {
        m_lastError = "Host not set";
        return false;
    }

    if (remotePath.isEmpty() || localPath.isEmpty()) {
        m_lastError = "Remote path or local path is empty";
        return false;
    }

    // 构建 FTP URL
    QUrl url;
    url.setScheme("ftp");
    url.setHost(m_host);
    url.setPort(m_port);
    url.setPath(remotePath);

    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    bool success = false;

    QNetworkReply *reply = manager.get(QNetworkRequest(url));

    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QFile file(localPath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
                success = true;
            } else {
                m_lastError = "Cannot write to local file";
            }
        } else {
            m_lastError = reply->errorString();
        }
        eventLoop.quit();
    });

    // 等待下载完成
    eventLoop.exec();
    reply->deleteLater();

    return success;
}

QString Upload::ErrorString() const
{
    return m_lastError;
}
