#include "processview.h"
#include "ui_processview.h"

#include "Model/processmodel.h"

ProcessView::ProcessView(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ProcessView)
{
    ui->setupUi(this);
    InitApp();
    InitData();
    InitConnect();
}

ProcessView::~ProcessView()
{
    delete ui;
}

void ProcessView::SetSize(int v_width,int v_height){
    width = v_width;
    height = v_height;
}

void ProcessView::showEvent(QShowEvent *event){
    //显示事件
    QString v_str_0,v_str_1,v_str_4,v_str_5;
    QStringList v_str_3;
    quint32 v_str_2;
    GlobalSet::GetProcessWindow(v_str_0,v_str_1,v_str_2,v_str_3,v_str_4,v_str_5);
    setWindowTitle(v_str_0);
    ui->MainProcessView->setColumnCount(v_str_2);
    ui->MainProcessView->setHorizontalHeaderLabels(v_str_3);
    QFile v_file(v_str_1);
    v_file.open(QIODevice::ReadOnly);
    QString v_style = v_file.readAll();
    v_file.close();
    setStyleSheet(v_style);
    setFixedSize(width,height);
}

void ProcessView::closeEvent(QCloseEvent *event)
{
    event->ignore(); // 忽略关闭事件
    hide(); // 隐藏窗口
}

void ProcessView::keyPressEvent(QKeyEvent *event){
    if (event->modifiers() & Qt::ControlModifier) {
        if(event->key()==Qt::Key_K){
            hide();
        }
    }
}

void ProcessView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        t_dragging = true;
        t_dragPosition = event->pos();  // 保存相对位置
        this->setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    QWidget::mousePressEvent(event);
}

void ProcessView::mouseMoveEvent(QMouseEvent *event) {
    if (t_dragging) {
        QPoint newPos = event->globalPos() - t_dragPosition;
        this->move(newPos);
        event->accept();
    }
    QWidget::mouseMoveEvent(event);
}

void ProcessView::mouseReleaseEvent(QMouseEvent *event) {
    if (t_dragging) {
        t_dragging = false;
        this->setCursor(Qt::ArrowCursor);
        this->releaseMouse();  // 释放鼠标捕获
        event->accept();
    }
    QWidget::mouseReleaseEvent(event);
}

void ProcessView::InitApp(){
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
}

void ProcessView::InitData(){
    t_process_model = new ProcessModel;
    t_dragging = false;
}

void ProcessView::InitConnect(){
}

void ProcessView::FlushData(){
    QString v_str = GlobalData::GetProcessMsg();
    if(v_str == "NODATAS"){
        return;
    }
    t_process_model->AntiSerial(v_str);
    QMap<QString,ProcessMsg> v_process_map= t_process_model->GetProcessMsg();
    ui->MainProcessView->clearContents();
    int row = 0;
    int cnt = v_process_map.count();
    ui->MainProcessView->setRowCount(cnt);
    for (auto it = v_process_map.begin(); it != v_process_map.end(); ++it, row++) {
        QString v_processName = it.key();  // 获取键：进程名
        const ProcessMsg& v_process_stru = it.value();  // 获取值：进程信息结构体
        QString temp;
        // 使用实际数据填充表格
        if(v_process_stru.alive){
            temp = "alive";
        }else{
            temp = "stop";
        }
        ui->MainProcessView->setItem(row, 0, new QTableWidgetItem(v_processName));  // 进程名
        ui->MainProcessView->setItem(row, 1, new QTableWidgetItem(v_process_stru.process_id));  // 进程号
        ui->MainProcessView->setItem(row, 2, new QTableWidgetItem(temp));  // 存活状态
        ui->MainProcessView->setItem(row, 3, new QTableWidgetItem(v_process_stru.start_time));  // 进程时间
        ui->MainProcessView->setItem(row, 4, new QTableWidgetItem(v_process_stru.elapsed_time));  // 启动时间
        //here
    }
}

void ProcessView::FlushButton(){
    FlushData();
}

void ProcessView::HideButton(){
    hide();
}
