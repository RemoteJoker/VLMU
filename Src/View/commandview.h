#ifndef COMMANDVIEW_H
#define COMMANDVIEW_H

#include "ViewImpl/viewimpl.h"

namespace Ui {
class CommandView;
}

class CommandView final: public QWidget
{
    Q_OBJECT

public:
    explicit CommandView(QWidget *parent = nullptr);
    void SetSize(int v_width,int v_height);
    ~CommandView();

signals:
    void SendCommand(int v_command);

protected:
    void closeEvent(QCloseEvent *event) override;
public:
    void InitApp();
private:
    void InitData();
    void InitConnect();

    void DumpSlot();
    void VersionSlot();
    void LogInfoSlot();

private:
    Ui::CommandView *ui;
    quint32 width;
    quint32 height;
};

#endif // COMMANDVIEW_H
