#include "configure.h"
#include <QDebug>
Configure::Configure(QString v_cfg_path)
{
    g_cfg_path = v_cfg_path;
}

bool Configure::InitDatabase() {
    try {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        QString v_db_path = g_cfg_path + "/bin/bootconf.db";
        m_db.setDatabaseName(v_db_path);
        if (m_db.open()) {
            return true;
        } else {
            throw std::runtime_error(QString("数据库打开失败").toStdString());
        }
    } catch (const std::runtime_error& e) {
        //数据库打开失败错误
        return false;
    }
}

QStringList Configure::ReadDatabaseConfig() {
    try {
        QStringList v_list;
        QSqlQuery query(m_db);
        if(!query.exec("SELECT last_boot_success_software_path, last_boot_success_software_version, new_software_path, new_software_version FROM boot_conf WHERE id = 1")){
            throw std::runtime_error(QString("数据查询失败-1").toStdString());
        }
        if(!query.next()){
            throw std::runtime_error(QString("数据查询失败-2").toStdString());
        }
        // 读取新版本号和旧版本号（处理空值）
        v_list<<g_cfg_path+query.value("last_boot_success_software_path").toString().replace("\"", "");
        v_list<<query.value("last_boot_success_software_version").toString();
        v_list<<g_cfg_path+query.value("new_software_path").toString().replace("\"", "");
        v_list<<query.value("new_software_version").toString();
        return v_list;
    } catch (const std::runtime_error& e) {
        return QStringList();
    }
}
