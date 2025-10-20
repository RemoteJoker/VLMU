#include "commandview.h"
#include "ui_commandview.h"

CommandView::CommandView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandView)
{
    ui->setupUi(this);
    InitData();
    InitConnect();
}

CommandView::~CommandView()
{
    delete ui;
}

void CommandView::SetSize(int v_width,int v_height){
    width = v_width;
    height = v_height;
}

void CommandView::InitApp(){
    QString v_str_0,v_str_1,v_str_2,v_str_3,v_str_4;
    GlobalSet::GetCmdWindow(v_str_0,v_str_1,v_str_2,v_str_3,v_str_4);
    setWindowTitle(v_str_0);
    ui->l1->setText(v_str_2);
    ui->l2->setText(v_str_3);
    ui->l3->setText(v_str_4);
    ui->Btn1->setText("获取"+v_str_2);
    ui->Btn2->setText("获取"+v_str_3);
    ui->Btn3->setText("获取"+v_str_4);
    QFile v_file(v_str_1);
    v_file.open(QIODevice::ReadOnly);
    QString v_style = v_file.readAll();
    v_file.close();
    setStyleSheet(v_style);
    setFixedSize(width,height);
}

void CommandView::InitData(){
}

void CommandView::InitConnect(){
    connect(ui->Btn1,&QPushButton::clicked,this,&CommandView::DumpSlot);
    connect(ui->Btn2,&QPushButton::clicked,this,&CommandView::VersionSlot);
    connect(ui->Btn3,&QPushButton::clicked,this,&CommandView::LogInfoSlot);
}

void CommandView::closeEvent(QCloseEvent *event)
{
    event->ignore(); // 忽略关闭事件
    hide(); // 隐藏窗口
}

void CommandView::DumpSlot(){
    QJsonObject v_json_obj;
    v_json_obj["request_id"] = QUuid::createUuid().toString(); // 生成UUID
    v_json_obj["timestamp"] = Utils::GetTimeStampS();
    // 转换为JSON字符串
    QJsonDocument doc(v_json_obj);
    QString v_str = doc.toJson(QJsonDocument::Compact);
    GlobalData::SetCoreInfo(v_str);
    emit SendCommand(Dump);
    QString v_log = "获取转储信息"+v_str;
    ui->CommandLog->append(v_log);
}

void CommandView::VersionSlot(){
    QJsonObject v_json_obj;
    v_json_obj["request_id"] = QUuid::createUuid().toString(); // 生成UUID
    v_json_obj["timestamp"] = Utils::GetTimeStampS();
    // 转换为JSON字符串
    QJsonDocument doc(v_json_obj);
    QString v_str = doc.toJson(QJsonDocument::Compact);
    GlobalData::SetVersionInfo(v_str);
    QString v_log = "获取版本信息"+v_str;
    ui->CommandLog->append(v_log);
    emit SendCommand(Version);
}

void CommandView::LogInfoSlot(){
    QJsonObject v_json_obj;
    v_json_obj["request_id"] = QUuid::createUuid().toString(); // 生成UUID
    v_json_obj["timestamp"] = Utils::GetTimeStampS();
    // 转换为JSON字符串
    QJsonDocument doc(v_json_obj);
    QString v_str = doc.toJson(QJsonDocument::Compact);
    GlobalData::SetLogInfo(v_str);
    QString v_log = "获取日志信息"+v_str;
    ui->CommandLog->append(v_log);
    emit SendCommand(LogInfo);
}
