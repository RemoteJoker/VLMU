#include "setview.h"
#include "ui_setview.h"

SetView::SetView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetView)
{
    ui->setupUi(this);
    InitData();
    InitConnect();
}

SetView::~SetView()
{
    delete ui;
}

void SetView::SetSize(int v_width,int v_height){
    width = v_width;
    height = v_height;
}

void SetView::InitApp(){
    QString v_str_0,v_str_1;
    GlobalSet::GetSetWindow(v_str_0,v_str_1);
    setWindowTitle(v_str_0);
    QFile v_file(v_str_1);
    v_file.open(QIODevice::ReadOnly);
    QString v_style = v_file.readAll();
    v_file.close();
    setStyleSheet(v_style);
    setFixedSize(width,height);
}

void SetView::InitData(){
    ui->AutoRadioButton->setChecked(true);
}

void SetView::InitConnect(){
    connect(ui->OkBtn,&QPushButton::clicked,this,&SetView::SaveSettings);
    connect(ui->AutoRadioButton,&QRadioButton::clicked,this,[=](){
        model = Auto;
    });
    connect(ui->UnAutoRadioButton,&QRadioButton::clicked,this,[=](){
        model = UnAuto;
    });
}

void SetView::closeEvent(QCloseEvent *event)
{
    event->ignore(); // 忽略关闭事件
    hide(); // 隐藏窗口
}

void SetView::SaveSettings(){
    //保存设置
    GlobalSet::SetAttribute(ui->WidthSpinBox->value(),ui->HeightSpinBox->value(),model);
    GlobalSet::SetFlag(Enable);
    hide();
}
