#ifndef UPLOAD_H
#define UPLOAD_H

#include "Upload_global.h"
#include <QtCore>

class UPLOAD_EXPORT Upload
{
public:
    Upload();
    // 设置服务器信息（一次性设置，可重复使用）
    void SetServer(const QString& host, quint16 port = 21);

    // 检查更新信息
    bool CheckUpdate(const QString& remotePath, const QString& v_version);

    // 核心下载函数 - 同步阻塞，在线程中调用
    bool Download(const QString& remotePath, const QString& localPath);

    // 获取错误信息（失败时调用）
    QString ErrorString() const;

private:
    QString m_host;
    quint16 m_port;
    QString m_lastError;
};

#endif // UPLOAD_H
