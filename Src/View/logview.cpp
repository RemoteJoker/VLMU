#include "logview.h"
#include "ui_logview.h"

#include "Model/loginfomodel.h"

LogView::LogView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::LogView)
{
    ui->setupUi(this);
    InitApp();
    InitData();
    InitConnect();
}

LogView::~LogView()
{
    delete ui;
}

void LogView::SetSize(int v_width,int v_height){
    width = v_width;
    height = v_height;
}

void LogView::showEvent(QShowEvent *event){
    QString v_str_0,v_str_1,v_str_2,v_str_3;
    GlobalSet::GetLogWindow(v_str_0,v_str_1,v_str_2,v_str_3);
    setWindowTitle(v_str_0);
    QFile v_file(v_str_1);
    v_file.open(QIODevice::ReadOnly);
    QString v_style = v_file.readAll();
    v_file.close();
    setStyleSheet(v_style);
    setFixedSize(width,height);
}

void LogView::keyPressEvent(QKeyEvent *event){
    if (event->modifiers() & Qt::ControlModifier) {
        if(event->key()==Qt::Key_K){
            hide();
        }
    }
}

void LogView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        t_dragging = true;
        t_dragPosition = event->pos();  // 保存相对位置
        this->setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void LogView::mouseMoveEvent(QMouseEvent *event) {
    if (t_dragging) {
        QPoint newPos = event->globalPos() - t_dragPosition;
        this->move(newPos);
        event->accept();
    }
    QWidget::mouseMoveEvent(event);
}

void LogView::mouseReleaseEvent(QMouseEvent *event) {
    if (t_dragging) {
        t_dragging = false;
        this->setCursor(Qt::ArrowCursor);
        this->releaseMouse();  // 释放鼠标捕获
        event->accept();
    }
    QWidget::mouseReleaseEvent(event);
}

void LogView::InitApp(){
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
}

void LogView::InitData(){
    t_info_model = new LogInfoModel;
}

void LogView::InitConnect(){
}

void LogView::closeEvent(QCloseEvent *event)
{
    event->ignore(); // 忽略关闭事件
    hide(); // 隐藏窗口
}

void LogView::FlushData(){
    // 一次性获取所有消息
    QString v_str = GlobalData::GetLogInfoMsg();
    if(v_str == "NODATAS"){
        return;
    }
    ui->MainLogView->clear();
    t_info_model->AntiSerial(v_str);
    QStringList allLogs = t_info_model->GetLogInfoMsg();
    // 批量添加
    for(const QString &logMsg : allLogs) {
        ui->MainLogView->addItem(logMsg);
    }
}

void LogView::FlushButton(){
    FlushData();
}

void LogView::HideButton(){
    hide();
}
