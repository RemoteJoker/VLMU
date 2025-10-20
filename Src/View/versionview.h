#ifndef VERSIONVIEW_H
#define VERSIONVIEW_H

#include "ViewImpl/viewimpl.h"

namespace Ui {
class VersionView;
}

class VersionModel;

class VersionView final: public QDockWidget
{
    Q_OBJECT

public:
    explicit VersionView(QWidget *parent = nullptr);
    void SetSize(int v_width,int v_height);
    ~VersionView();

protected:
    void showEvent(QShowEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

public slots:
    void FlushData();

private slots:
    void FlushButton();
    void HideButton();

private:
    void InitApp();
    void InitData();
    void InitConnect();

private:
    Ui::VersionView *ui;
    bool t_dragging;
    QPoint t_dragPosition;
    VersionModel *t_version_model;
    quint32 width;
    quint32 height;
};

#endif // VERSIONVIEW_H
