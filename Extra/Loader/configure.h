#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QVersionNumber>

#include <stdexcept>

class Configure
{
public:
    Configure(QString);

    bool InitDatabase();//初始化数据库

    QStringList ReadDatabaseConfig();

private:
    QString g_cfg_path;//全局目录
    QSqlDatabase m_db;//数据库链接对象
};

#endif // CONFIGURE_H
