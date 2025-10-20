#ifndef DUMPVIEW_H
#define DUMPVIEW_H

#include "ViewImpl/viewimpl.h"

namespace Ui {
class DumpView;
}

class CoreDumpModel;

class DumpView final: public QDockWidget
{
    Q_OBJECT

public:
    explicit DumpView(QWidget *parent = nullptr);
    void SetSize(int v_width,int v_height);
    ~DumpView();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void FlushData();

private:
    void InitApp();
    void InitData();
    void InitConnect();

private slots:
    void FlushButton();
    void HideButton();

private:
    Ui::DumpView *ui;
    bool t_dragging;
    QPoint t_dragPosition;
    CoreDumpModel *t_core_dump_model;
    quint32 width;
    quint32 height;
};

#endif // DUMPVIEW_H
