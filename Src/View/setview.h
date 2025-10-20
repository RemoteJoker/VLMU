#ifndef SETVIEW_H
#define SETVIEW_H

#include "ViewImpl/viewimpl.h"

namespace Ui {
class SetView;
}

class SetView final: public QWidget
{
    Q_OBJECT

public:
    explicit SetView(QWidget *parent = nullptr);
    void SetSize(int v_width,int v_height);
    ~SetView();

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    void InitApp();
private:
    void InitData();
    void InitConnect();

private slots:
    void SaveSettings();

private:
    Ui::SetView *ui;
    quint32 width;
    quint32 height;
    quint32 model;
};

#endif // SETVIEW_H
