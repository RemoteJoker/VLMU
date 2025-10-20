#include "aboutview.h"
#include "ui_aboutview.h"

AboutView::AboutView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutView)
{
    ui->setupUi(this);
    InitData();
    InitConnect();
}

AboutView::~AboutView()
{
    delete ui;
}

void AboutView::SetSize(int v_width,int v_height){
    width = v_width;
    height = v_height;
}

void AboutView::InitApp(){
    QString v_str_0,v_str_1;
    GlobalSet::GetAboutWindow(v_str_0,v_str_1);
    setWindowTitle(v_str_0);
    QFile v_file(v_str_1);
    v_file.open(QIODevice::ReadOnly);
    QString v_style = v_file.readAll();
    v_file.close();
    setStyleSheet(v_style);
    setFixedSize(width,height);
    ui->VersionLabel->setFixedSize(width,height);
}

void AboutView::InitData(){
    QString v_str = "VLMU前端显示软件\n"
                    "测试版";
    ui->VersionLabel->setEnabled(false);
    ui->VersionLabel->setText(v_str);
}

void AboutView::InitConnect(){
}

void AboutView::closeEvent(QCloseEvent *event)
{
    event->ignore(); // 忽略关闭事件
    hide(); // 隐藏窗口
}
