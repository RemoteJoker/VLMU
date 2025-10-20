#ifndef ABOUTVIEW_H
#define ABOUTVIEW_H

#include "ViewImpl/viewimpl.h"

namespace Ui {
class AboutView;
}

class AboutView final: public QWidget
{
    Q_OBJECT

public:
    explicit AboutView(QWidget *parent = nullptr);
    void SetSize(int v_width,int v_height);
    ~AboutView();

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    void InitApp();
private:
    void InitData();
    void InitConnect();

private:
    Ui::AboutView *ui;
    quint32 width;
    quint32 height;
};

#endif // ABOUTVIEW_H
