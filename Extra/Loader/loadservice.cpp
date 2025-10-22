#include "loadservice.h"

LoadService::LoadService(){
}

bool LoadService::initService(){
    try {
        g_configure = QSharedPointer<Configure>(new Configure(QCoreApplication::applicationDirPath()));
        m_statusMessage = "数据库初始化";
        emit statusMessageChanged();
        if(!g_configure->InitDatabase()){
            m_statusMessage = "数据库打开失败";
            emit statusMessageChanged();
            return false;
        }else{
            m_statusMessage = "数据库打开成功";
            emit statusMessageChanged();
        }
        QStringList v_cfg_list = g_configure->ReadDatabaseConfig();
        if(!v_cfg_list.isEmpty()){
            m_statusMessage = "数据库读取成功";
            emit statusMessageChanged();
            if(v_cfg_list.size() == 4){
                m_old_version_path = v_cfg_list[0];
                m_old_version = v_cfg_list[1];
                m_new_version_path = v_cfg_list[2];
                m_new_version = v_cfg_list[3];
                m_cfg_flag = true;
            }else{
                m_cfg_flag = false;
                throw std::runtime_error(QString("数据库字段不完整").toStdString());
            }
        }else{
            m_statusMessage = "数据库读取失败";
            emit statusMessageChanged();
            m_cfg_flag = false;
            return false;
        }
        return true;
    } catch (const std::runtime_error& e) {
        m_statusMessage = QString("数据库字段不完整");
        emit statusMessageChanged();
        return false;
    }
}

bool LoadService::launchProgram(){
    try {
        // 1. 先尝试启动最高版本
        if (!m_new_version_path.isEmpty()) {
            QFileInfo highestFile(m_new_version_path);
            m_statusMessage = "启动新版本";
            emit statusMessageChanged();
            if (highestFile.exists()) {
                // 启动最高版本
                if (QProcess::startDetached(m_new_version_path)) {
                    m_statusMessage = "最高版本启动成功";
                    emit statusMessageChanged();
                    return true; // 启动成功，直接返回
                } else {
                    m_statusMessage = "最高版本启动失败，尝试启动旧版本...";
                    emit statusMessageChanged();
                }
            } else {
                m_statusMessage = "最新版本软件不存在，尝试启动旧版本...";
                emit statusMessageChanged();
            }
        } else {
            m_statusMessage = "最新版本软件不存在，尝试启动旧版本...";
            emit statusMessageChanged();
        }
        // 2. 最高版本启动失败，重试旧版本路径
        if (!m_old_version_path.isEmpty()) {
            QFileInfo oldFile(m_old_version_path);
            if (oldFile.exists()) {
                m_statusMessage = "启动旧版本";
                emit statusMessageChanged();
                if (QProcess::startDetached(m_old_version_path)) {
                    m_statusMessage = "旧版本启动成功";
                    emit statusMessageChanged();
                    return true;
                } else {
                    m_statusMessage = "旧版本启动失败";
                    emit statusMessageChanged();
                }
            } else {
                m_statusMessage = "错误：旧版本软件不存在";
                emit statusMessageChanged();
            }
        } else {
            m_statusMessage = "错误：旧版本软件不存在";
            emit statusMessageChanged();
        }
        return false;
    } catch (...) {
        m_statusMessage = "启动软件时发生未知异常";
        emit statusMessageChanged();
        return false;
    }
}

bool LoadService::getCfgPath(){
    return m_cfg_flag;
}

QString LoadService::getStatusMessage(){
    return m_statusMessage;
}
