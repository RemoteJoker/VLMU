#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "View/processview.h"
#include "View/aboutview.h"
#include "View/setview.h"
#include "View/dumpview.h"
#include "View/versionview.h"
#include "View/logview.h"
#include "View/commandview.h"
#include "Service/controlservice.h"

#include <QTimer>
#include <QSystemTrayIcon>

MainWindow::MainWindow(class ContrlService *v_control_service,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    g_control_service = v_control_service;
    InitApp();
    InitData();
    InitConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 检查是否按下Ctrl键
    if (event->modifiers() & Qt::ControlModifier) {
        // 检查按键是否是1-9
        switch (event->key()) {
        case Qt::Key_F1:
            HandleCtrlNumber(Ctrl_F1);
            event->accept();
            return;
        case Qt::Key_F2:
            HandleCtrlNumber(Ctrl_F2);
            event->accept();
            return;
        case Qt::Key_F3:
            HandleCtrlNumber(Ctrl_F3);
            event->accept();
            return;
        case Qt::Key_F4:
            HandleCtrlNumber(Ctrl_F4);
            event->accept();
            return;
        case Qt::Key_F5:
            HandleCtrlNumber(Ctrl_F5);
            event->accept();
            return;
        case Qt::Key_F6:
            HandleCtrlNumber(Ctrl_F6);
            event->accept();
            return;
        case Qt::Key_F7:
            HandleCtrlNumber(Ctrl_F7);
            event->accept();
            return;
        case Qt::Key_F8:
            HandleCtrlNumber(Ctrl_F8);
            event->accept();
            return;
        case Qt::Key_F9:
            HandleCtrlNumber(Ctrl_F9);
            event->accept();
            return;
        case Qt::Key_1:
            HandleCtrlNumber(Ctrl_1);
            event->accept();
            return;
        case Qt::Key_2:
            HandleCtrlNumber(Ctrl_2);
            event->accept();
            return;
        case Qt::Key_3:
            HandleCtrlNumber(Ctrl_3);
            event->accept();
            return;
        case Qt::Key_4:
            HandleCtrlNumber(Ctrl_4);
            event->accept();
            return;
        case Qt::Key_5:
            HandleCtrlNumber(Ctrl_5);
            event->accept();
            return;
        case Qt::Key_6:
            HandleCtrlNumber(Ctrl_6);
            event->accept();
            return;
        case Qt::Key_7:
            HandleCtrlNumber(Ctrl_7);
            event->accept();
            return;
        case Qt::Key_8:
            HandleCtrlNumber(Ctrl_8);
            event->accept();
            return;
        case Qt::Key_9:
            HandleCtrlNumber(Ctrl_9);
            event->accept();
            return;
        case Qt::Key_H:
            HandleCtrlNumber(Ctrl_H);
            event->accept();
            return;
        default:
            break;
        }
    }

    QWidget::keyPressEvent(event);
}

void MainWindow::InitApp(){
    Log(L_INFO,"主界面初始化-0");
    g_timer = new QTimer;

    /*托盘创建*/
    g_system_tray_icon = new QSystemTrayIcon;
    g_system_tray_icon->setIcon(QIcon(Utils::GetRunPath()+"/configure/pic/ico.ico"));
    g_tray_menu = new QMenu;
    g_exit_action = new QAction("退出");
    g_tray_menu->addAction(g_exit_action);
    g_system_tray_icon->setContextMenu(g_tray_menu);
    g_system_tray_icon->show();
    /*托盘创建*/

    QString v_str_0,v_str_1,v_str_2,v_str_5,v_str_6,v_str_7,v_str_8,v_str_9,v_str_10,v_str_11,v_str_12,v_str_13,v_str_14,v_str_15,v_str_16;
    quint32 v_str_3,v_str_4;
    GlobalSet::GetMainWindow(v_str_0,v_str_1,v_str_2,v_str_3,
                             v_str_4,v_str_5,v_str_6,v_str_7,
                             v_str_8,v_str_9,v_str_10,v_str_11,
                             v_str_12,v_str_13,v_str_14,v_str_15,
                             v_str_16);
    setWindowTitle(v_str_0+QString("--")+v_str_1);
    setFixedSize(v_str_3,v_str_4);
    m_mainwindow_width = v_str_3;
    m_mainwindow_height = v_str_4;
    setWindowIcon(QIcon(":/Src/Picture/ico.ico"));
    //ui->Menu0->setTitle(v_str_5);先屏蔽
    ui->Menu1->setTitle(v_str_6);
    ui->Menu2->setTitle(v_str_9);
    //ui->Menu3->setTitle(v_str_14);先屏蔽
    ui->Menu4->setTitle(v_str_15);

    ui->Menu1Action0->setText(v_str_7);
    ui->Menu1Action1->setText(v_str_8);
    ui->Menu2Action0->setText(v_str_10);
    ui->Menu2Action1->setText(v_str_11);
    ui->Menu2Action2->setText(v_str_12);
    ui->Menu2Action3->setText(v_str_13);
    ui->Menu4Action0->setText(v_str_16);

    ui->ToolBar->addWidget(ui->ProcessToolBtn);
    ui->ToolBar->addWidget(ui->DumpToolBtn);
    ui->ToolBar->addWidget(ui->VersionToolBtn);
    ui->ToolBar->addWidget(ui->LogToolBtn);

    ui->BackWidget->setFixedSize(v_str_3,v_str_4);

    ui->CpuGroupBox->setFixedSize(v_str_3/2,v_str_4/2*0.85);
    ui->GpuGroupBox->setFixedSize(v_str_3/2,v_str_4/2*0.85);
    ui->MemoryGroupBox->setFixedSize(v_str_3/2,v_str_4/2*0.85);
    ui->DiskGroupBox->setFixedSize(v_str_3/2,v_str_4/2*0.85);
    ui->CpuGroupBox->move(0,0);
    ui->GpuGroupBox->move(v_str_3/2,0);
    ui->MemoryGroupBox->move(0,v_str_4/2*0.85);
    ui->DiskGroupBox->move(v_str_3/2,v_str_4/2*0.85);
    ui->CpuLabel->setFixedSize(v_str_3/2,v_str_4/2);
    ui->GpuLabel->setFixedSize(v_str_3/2,v_str_4/2);
    ui->MemoryLabel->setFixedSize(v_str_3/2,v_str_4/2);
    ui->DiskLabel->setFixedSize(v_str_3/2,v_str_4/2);

    QFile v_file(v_str_2);
    v_file.open(QIODevice::ReadOnly);
    QString v_style = v_file.readAll();
    v_file.close();
    this->setStyleSheet(v_style);

    Log(L_INFO,"主界面初始化-1");
}

void MainWindow::InitData(){
    v_about_view = new AboutView;

    v_process_view = new ProcessView;
    v_dump_view = new DumpView;
    v_version_view = new VersionView;
    v_log_view = new LogView;

    v_set_view = new SetView;
    v_command_view = new CommandView;

    g_magic = 0;
    g_breath = 0;
    g_is_first_connect = false;
    g_timer->start(500);

    Log(L_INFO,"主界面初始化-2");
}

void MainWindow::InitConnect(){
    //UI与控制核心通信
    connect(g_control_service,&ContrlService::SendCodeToWindow,this,&MainWindow::RecvCode);
    connect(this,&MainWindow::SendCode,g_control_service,&ContrlService::RecCodeFromWindow);
    //UI与命令通信
    connect(v_command_view,&CommandView::SendCommand,this,&MainWindow::RecCommand);

    connect(ui->Menu1Action0,&QAction::triggered,this,&MainWindow::CommandViewSlot);
    connect(ui->Menu1Action1,&QAction::triggered,this,&MainWindow::SetViewSlot);
    connect(ui->Menu2Action0,&QAction::triggered,this,&MainWindow::ProcessViewSlot);
    connect(ui->Menu2Action1,&QAction::triggered,this,&MainWindow::DumpViewSlot);
    connect(ui->Menu2Action2,&QAction::triggered,this,&MainWindow::VersionViewSlot);
    connect(ui->Menu2Action3,&QAction::triggered,this,&MainWindow::LogViewSlot);
    connect(ui->Menu4Action0,&QAction::triggered,this,&MainWindow::AboutViewSlot);

    connect(ui->ProcessToolBtn,&QToolButton::clicked,this,&MainWindow::ProcessViewSlot);
    connect(ui->DumpToolBtn,&QToolButton::clicked,this,&MainWindow::DumpViewSlot);
    connect(ui->VersionToolBtn,&QToolButton::clicked,this,&MainWindow::VersionViewSlot);
    connect(ui->LogToolBtn,&QToolButton::clicked,this,&MainWindow::LogViewSlot);

    //connect(ui->Menu4Action0,&QAction::triggered,this,&MainWindow::ShowStatusMessage);状态栏消息
    connect(g_timer,&QTimer::timeout,this,&MainWindow::TimerEvent);//计时器槽函数

    //托盘槽函数
    connect(g_exit_action,&QAction::triggered,this,[=](){this->close();});//退出按钮
    //托盘槽函数

    Log(L_INFO,"主界面初始化-3");
}

void MainWindow::RecvCode(int v_service_id,int v_code_type){
    if(v_service_id == Control){
        switch(v_code_type){
        case UnDefineError:{
            //Error
        }break;
        case HasNewProcessSourceData:{
            //有新的进程信息到达
            Log(L_INFO,"有新的进程信息到达");
            v_process_view->FlushData();
        }break;
        case HasNewCoreDumpSourceData:{
            //有新的内核转储信息到达
            Log(L_INFO,"有新的内核转储信息到达");
            v_dump_view->FlushData();
        }break;
        case HasNewVersionSourceData:{
            //有新的版本信息到达
            Log(L_INFO,"有新的版本信息到达");
            v_version_view->FlushData();
        }break;
        case HasNewLogSourceData:{
            //有新的日志信息到达
            Log(L_INFO,"有新的日志信息到达");
            v_log_view->FlushData();
        }
        default:break;
        }
    }
    if(v_service_id == Data){
        switch(v_code_type){
        case UnDefineError:{
            //Error
        }break;
        default:break;
        }
    }
    if(v_service_id == Net){
        switch(v_code_type){
        case UnDefineError:{
            //Error
        }break;
        case HeartData:{
            //心跳包处理逻辑
            g_breath = 0;
            if(!g_is_first_connect){
                //主动拉一次请求
                g_system_tray_icon->showMessage("提示","上线拉取请求",QSystemTrayIcon::Information,1000);
                Log(L_INFO,"上线拉取请求");
                QJsonObject v_json_obj;
                v_json_obj["request_id"] = QUuid::createUuid().toString(); // 生成UUID
                v_json_obj["timestamp"] = Utils::GetTimeStampS();
                // 转换为JSON字符串
                QJsonDocument doc(v_json_obj);
                QString v_str = doc.toJson(QJsonDocument::Compact);
                GlobalData::SetCoreInfo(v_str);
                GlobalData::SetVersionInfo(v_str);
                GlobalData::SetLogInfo(v_str);
                SendCode(Control,GetDumpData);
                SendCode(Control,GetVersionData);
                SendCode(Control,GetLogData);
            }
            g_is_first_connect = true;
            ShowStatusMessage("下位机已链接");
        }break;
        default:break;
        }
    }
    if(v_service_id == Sql){
        switch(v_code_type){
        case UnDefineError:{
            //Error
        }break;
        default:break;
        }
    }
}

void MainWindow::RecCommand(int v_code_type){
    switch(v_code_type){
    case Dump:{
        //Dump
        Log(L_INFO,"发送Dump请求");
        SendCode(Control,GetDumpData);
    }break;
    case Version:{
        //Version
        Log(L_INFO,"发送版本请求");
        SendCode(Control,GetVersionData);
    }break;
    case LogInfo:{
        //LogInfo
        Log(L_INFO,"发送日志请求");
        SendCode(Control,GetLogData);
    }break;
    default:break;
    }
}

void MainWindow::HandleCtrlNumber(int v_index){
    switch (v_index) {
    case Ctrl_1:{ProcessViewSlot();}break;
    case Ctrl_2:{DumpViewSlot();}break;
    case Ctrl_3:{VersionViewSlot();}break;
    case Ctrl_4:{LogViewSlot();}break;
    case Ctrl_5:{}break;
    case Ctrl_6:{}break;
    case Ctrl_7:{}break;
    case Ctrl_8:{}break;
    case Ctrl_9:{}break;
    case Ctrl_F1:{CommandViewSlot();}break;
    case Ctrl_F2:{}break;
    case Ctrl_F3:{}break;
    case Ctrl_F4:{}break;
    case Ctrl_F5:{}break;
    case Ctrl_F6:{}break;
    case Ctrl_F7:{}break;
    case Ctrl_F8:{}break;
    case Ctrl_F9:{SetViewSlot();}break;
    case Ctrl_H:{AboutViewSlot();}break;
    default:{}break;
    }
}

void MainWindow::TimerEvent(){
    g_magic+=500;//强相关
    quint32 v_data_model,v_flag_model;
    GlobalSet::GetDataModel(v_data_model);
    GlobalSet::GetFlag(v_flag_model);

    ui->CpuLabel->setText(Utils::GetCpuInfo());
    ui->GpuLabel->setText(Utils::GetGpuInfo());
    ui->MemoryLabel->setText(Utils::GetMemoryInfo());
    ui->DiskLabel->setText(Utils::GetDiskInfo());

    if(g_breath>20){
        //下位机未链接
        Log(L_WARN,"未检测到下位机");
        ShowStatusMessage("未检测到下位机");
    }
    if(v_data_model == Auto){
        //自动更新数据
        if(v_process_view->isVisible()){
            Log(L_INFO,"主动刷新进程数据");
            v_process_view->FlushData();
        }
        if(v_dump_view->isVisible()){
            Log(L_INFO,"主动刷新转储数据");
            v_dump_view->FlushData();
        }
        if(v_version_view->isVisible()){
            Log(L_INFO,"主动刷新版本数据");
            v_version_view->FlushData();
        }
        if(v_log_view->isVisible()){
            Log(L_INFO,"主动刷新日志数据");
            v_log_view->FlushData();
        }
        if(v_about_view->isVisible()){
        }
    }
    if(v_flag_model == Enable){
        //重新设置全局
        quint32 v_set_w,v_set_h,v_set_flag;
        GlobalSet::GetAttribute(v_set_w,v_set_h,v_set_flag);
        GlobalSet::SetDataModel(v_set_flag);
        this->setFixedSize(v_set_w,v_set_h);
        GlobalSet::SetFlag(UnEnable);//先关闭再重新设置
    }
    //提醒更新线程获取版本信息
    //1800000:半小时
    if(g_magic>1800000){
        Log(L_INFO,"定时请求-更新");
        emit SendCode(Control,GetUpdate);
        g_magic = 0;
    }
    g_breath++;
}

void MainWindow::CommandViewSlot(){
    g_system_tray_icon->showMessage("提示","打开命令转发界面",QSystemTrayIcon::Information,1000);
    Log(L_INFO,"打开命令转发界面");
    v_command_view->SetSize(m_mainwindow_width*0.6,m_mainwindow_width*0.6);
    v_command_view->InitApp();
    v_command_view->show();
}

void MainWindow::SetViewSlot(){
    g_system_tray_icon->showMessage("提示","打开系统设置界面",QSystemTrayIcon::Information,1000);
    Log(L_INFO,"打开系统设置界面");
    v_set_view->SetSize(m_mainwindow_width*0.2,m_mainwindow_width*0.15);
    v_set_view->InitApp();
    v_set_view->show();
}

void MainWindow::ProcessViewSlot(){
    g_system_tray_icon->showMessage("提示","打开进程信息界面",QSystemTrayIcon::Information,1000);
    Log(L_INFO,"打开进程信息界面");
    v_process_view->SetSize(m_mainwindow_width*0.57,m_mainwindow_height*0.66);
    this->addDockWidget(Qt::LeftDockWidgetArea, v_process_view);
    v_process_view->show();
}

void MainWindow::DumpViewSlot(){
    g_system_tray_icon->showMessage("提示","打开内核转储界面",QSystemTrayIcon::Information,1000);
    Log(L_INFO,"打开内核转储界面");
    v_dump_view->SetSize(m_mainwindow_width*0.57,m_mainwindow_height*0.66);
    this->addDockWidget(Qt::LeftDockWidgetArea, v_dump_view);
    v_dump_view->show();
}

void MainWindow::VersionViewSlot(){
    g_system_tray_icon->showMessage("提示","打开版本信息界面",QSystemTrayIcon::Information,1000);
    Log(L_INFO,"打开版本信息界面");
    v_version_view->SetSize(m_mainwindow_width*0.57,m_mainwindow_height*0.66);
    this->addDockWidget(Qt::LeftDockWidgetArea, v_version_view);
    v_version_view->show();
}

void MainWindow::LogViewSlot(){
    g_system_tray_icon->showMessage("提示","打开日志信息界面",QSystemTrayIcon::Information,1000);
    Log(L_INFO,"打开日志信息界面");
    v_log_view->SetSize(m_mainwindow_width*0.57,m_mainwindow_height*0.66);
    this->addDockWidget(Qt::LeftDockWidgetArea, v_log_view);
    v_log_view->show();
}

void MainWindow::AboutViewSlot(){
    g_system_tray_icon->showMessage("提示","打开关于界面",QSystemTrayIcon::Information,1000);
    Log(L_INFO,"打开关于界面");
    v_about_view->SetSize(m_mainwindow_width*0.3,m_mainwindow_width*0.3);
    v_about_view->InitApp();
    v_about_view->show();
}

void MainWindow::ShowStatusMessage(QString v_str){
    ui->StatusBar->showMessage(v_str);
}
