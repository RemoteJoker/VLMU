#include "versionview.h"
#include "ui_versionview.h"

#include "Model/versionmodel.h"

VersionView::VersionView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::VersionView)
{
    ui->setupUi(this);
    InitApp();
    InitData();
    InitConnect();
}

VersionView::~VersionView()
{
    delete ui;
}

void VersionView::SetSize(int v_width,int v_height){
    width = v_width;
    height = v_height;
}

void VersionView::keyPressEvent(QKeyEvent *event){
    if (event->modifiers() & Qt::ControlModifier) {
        if(event->key()==Qt::Key_K){
            hide();
        }
    }
}

void VersionView::showEvent(QShowEvent *event){
    QString v_str_0,v_str_1,v_str_2,v_str_3;
    GlobalSet::GetVersionWindow(v_str_0,v_str_1,v_str_2,v_str_3);
    setWindowTitle(v_str_0);
    QFile v_file(v_str_1);
    v_file.open(QIODevice::ReadOnly);
    QString v_style = v_file.readAll();
    v_file.close();
    setStyleSheet(v_style);
    setFixedSize(width,height);
}

void VersionView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        t_dragging = true;
        t_dragPosition = event->pos();  // 保存相对位置
        this->setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void VersionView::mouseMoveEvent(QMouseEvent *event) {
    if (t_dragging) {
        QPoint newPos = event->globalPos() - t_dragPosition;
        this->move(newPos);
        event->accept();
    }
    QWidget::mouseMoveEvent(event);
}

void VersionView::mouseReleaseEvent(QMouseEvent *event) {
    if (t_dragging) {
        t_dragging = false;
        this->setCursor(Qt::ArrowCursor);
        this->releaseMouse();  // 释放鼠标捕获
        event->accept();
    }
    QWidget::mouseReleaseEvent(event);
}

void VersionView::InitApp(){
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
}

void VersionView::InitData(){
    t_version_model = new VersionModel;
}

void VersionView::InitConnect(){
}

void VersionView::closeEvent(QCloseEvent *event)
{
    event->ignore(); // 忽略关闭事件
    hide(); // 隐藏窗口
}

void VersionView::FlushData(){
    QString v_str = GlobalData::GetVersionMsg();
    if(v_str == "NODATAS"){
        return;
    }
    ui->VersionScreen->clear();
    t_version_model->AntiSerial(v_str);
    QStringList allLogs = t_version_model->GetVersionMsg();
    for(QString v_str:allLogs){
        ui->VersionScreen->append(v_str);
    }
}

void VersionView::FlushButton(){
    FlushData();
}

void VersionView::HideButton(){
    hide();
}
