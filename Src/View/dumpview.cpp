#include "dumpview.h"
#include "ui_dumpview.h"

#include "Model/coredumpmodel.h"

DumpView::DumpView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::DumpView)
{
    ui->setupUi(this);
    InitApp();
    InitData();
    InitConnect();
}

DumpView::~DumpView()
{
    delete ui;
}

void DumpView::SetSize(int v_width,int v_height){
    width = v_width;
    height = v_height;
}

void DumpView::showEvent(QShowEvent *event){
    QString v_str_0,v_str_1,v_str_2,v_str_3;
    GlobalSet::GetDumpWindow(v_str_0,v_str_1,v_str_2,v_str_3);
    setWindowTitle(v_str_0);
    QFile v_file(v_str_1);
    v_file.open(QIODevice::ReadOnly);
    QString v_style = v_file.readAll();
    v_file.close();
    setStyleSheet(v_style);
    setFixedSize(width,height);
    ui->MainDumpView->setColumnCount(2);
    ui->MainDumpView->setHorizontalHeaderLabels(QStringList()<<"文件路径"<<"时间");
    ui->MainDumpView->setColumnWidth(0,width/2*0.95);
    ui->MainDumpView->setColumnWidth(1,width/2*0.95);
}

void DumpView::keyPressEvent(QKeyEvent *event){
    if (event->modifiers() & Qt::ControlModifier) {
        if(event->key()==Qt::Key_K){
            hide();
        }
    }
}

void DumpView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        t_dragging = true;
        t_dragPosition = event->pos();  // 保存相对位置
        this->setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void DumpView::mouseMoveEvent(QMouseEvent *event) {
    if (t_dragging) {
        QPoint newPos = event->globalPos() - t_dragPosition;
        this->move(newPos);
        event->accept();
    }
    QWidget::mouseMoveEvent(event);
}

void DumpView::mouseReleaseEvent(QMouseEvent *event) {
    if (t_dragging) {
        t_dragging = false;
        this->setCursor(Qt::ArrowCursor);
        this->releaseMouse();  // 释放鼠标捕获
        event->accept();
    }
    QWidget::mouseReleaseEvent(event);
}

void DumpView::InitApp(){
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    //ui->MainDumpView->resizeColumnsToContents();
}
void DumpView::InitData(){
    t_core_dump_model = new CoreDumpModel;
}

void DumpView::InitConnect(){
}

void DumpView::closeEvent(QCloseEvent *event)
{
    event->ignore(); // 忽略关闭事件
    hide(); // 隐藏窗口
}

void DumpView::FlushData(){
    QString v_str = GlobalData::GetCoreMsg();
    if(v_str == "NODATAS"){
        return;
    }
    ui->MainDumpView->clearContents();
    t_core_dump_model->AntiSerial(v_str);
    QStringList allLogs = t_core_dump_model->GetCoreMsg();
    // 批量添加
    int row = 0;
    for(const QString &logMsg : allLogs) {
        QStringList v_list = logMsg.split('@');
        ui->MainDumpView->insertRow(row);
        ui->MainDumpView->setItem(row,0,new QTableWidgetItem(v_list[0]));
        ui->MainDumpView->setItem(row,1,new QTableWidgetItem(v_list[1]));
        row++;
    }
}

void DumpView::FlushButton(){
    FlushData();
}

void DumpView::HideButton(){
    hide();
}
