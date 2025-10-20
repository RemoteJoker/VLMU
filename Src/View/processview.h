#ifndef PROCESSVIEW_H
#define PROCESSVIEW_H

#include "ViewImpl/viewimpl.h"

namespace Ui {
class ProcessView;
}

class ProcessModel;

class ProcessView final: public QDockWidget
{
    Q_OBJECT

public:
    explicit ProcessView(QWidget *parent = nullptr);
    void SetSize(int v_width,int v_height);
    ~ProcessView();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void InitApp();
    void InitData();
    void InitConnect();

public slots:
    void FlushData();

private slots:
    void FlushButton();
    void HideButton();

private:
    Ui::ProcessView *ui;
    bool t_dragging;
    QPoint t_dragPosition;
    ProcessModel *t_process_model;
    quint32 width;
    quint32 height;
};

#endif // PROCESSVIEW_H
