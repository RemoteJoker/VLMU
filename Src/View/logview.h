#ifndef LOGVIEW_H
#define LOGVIEW_H

#include "ViewImpl/viewimpl.h"

namespace Ui {
class LogView;
}

class LogInfoModel;

class LogView final: public QDockWidget
{
    Q_OBJECT

public:
    explicit LogView(QWidget *parent = nullptr);
    void SetSize(int v_width,int v_height);
    ~LogView();

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
    Ui::LogView *ui;
    bool t_dragging;
    QPoint t_dragPosition;
    LogInfoModel *t_info_model;
    quint32 width;
    quint32 height;
};

#endif // LOGVIEW_H
