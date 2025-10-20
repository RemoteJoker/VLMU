#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QKeyEvent;
class QSystemTrayIcon;
class QTimer;
class ContrlService;
class AboutView;
class CommandView;
class DumpView;
class LogView;
class ProcessView;
class SetView;
class VersionView;

enum KeyValue{
    Ctrl_F1,
    Ctrl_F2,
    Ctrl_F3,
    Ctrl_F4,
    Ctrl_F5,
    Ctrl_F6,
    Ctrl_F7,
    Ctrl_F8,
    Ctrl_F9,
    Ctrl_1,
    Ctrl_2,
    Ctrl_3,
    Ctrl_4,
    Ctrl_5,
    Ctrl_6,
    Ctrl_7,
    Ctrl_8,
    Ctrl_9,
    Ctrl_H,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(class ContrlService *v_control_service,QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void SendCode(int v_service_id,int v_code_type);

public slots:
    void RecvCode(int v_service_id,int v_code_type);
    void RecCommand(int v_code_type);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void InitApp();
    void InitData();
    void InitConnect();

private:
    void HandleCtrlNumber(int v_index);

//计时器槽函数
private slots:
    void TimerEvent();

//菜单槽函数
private slots:
    void CommandViewSlot();
    void SetViewSlot();

private slots:
    void ProcessViewSlot();
    void DumpViewSlot();
    void VersionViewSlot();
    void LogViewSlot();

private slots:
    void AboutViewSlot();
//菜单槽函数

private slots:
    void ShowStatusMessage(QString v_str);

private:
    Ui::MainWindow *ui;
    ContrlService* g_control_service;//主控制线程
    QTimer *g_timer;//全局计时器
    quint32 g_magic;//魔数，与更新相关
    quint32 g_breath;//呼吸，与心跳相关

    /*进程实例*/
    ProcessView *v_process_view;
    AboutView *v_about_view;
    SetView *v_set_view;
    DumpView *v_dump_view;
    VersionView *v_version_view;
    LogView *v_log_view;
    CommandView *v_command_view;

    quint32 m_mainwindow_width;
    quint32 m_mainwindow_height;
    bool g_is_first_connect;

    QSystemTrayIcon *g_system_tray_icon;
    QMenu *g_tray_menu;
    QAction *g_exit_action;
};
#endif // MAINWINDOW_H
