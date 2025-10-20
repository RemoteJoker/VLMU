#include "mainwindow.h"
#include "Service/controlservice.h"
#include "Service/dataservice.h"
#include "Service/netservice.h"
#include "Service/sqlservice.h"
#include "Service/updateservice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Utils::InitApp();
    //运行验证版本号是否正确
#ifndef QT_DEBUG
//    if(argc != 2){
//        return -1;
//    }
//    if(!Utils::InitApp()){
//        return -2;
//    }
#endif

    DataService *g_t_data = new DataService;
    NetService *g_t_net = new NetService;
    SqlService *g_t_sql = new SqlService;
    UpdateService *g_t_update = new UpdateService;
    ContrlService *g_t_control = new ContrlService(g_t_data,g_t_net,g_t_sql,g_t_update);

    g_t_data->start();
    g_t_net->start();
    g_t_sql->start();
    g_t_control->start();

    MainWindow w(g_t_control);
    w.show();
    Utils::SetRunPath();//退出程序的时候更新本次运行路径
    return a.exec();
}
