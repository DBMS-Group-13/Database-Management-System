#ifndef RNWINDOW_H
#define RNWINDOW_H

#include <QDialog>
#include "QMouseEvent"
#include "qmath.h"
#include "qpainter.h"

namespace Ui {
class rnWindow;
}

class rnWindow : public QDialog
{
    Q_OBJECT

public:
    explicit rnWindow(QWidget *parent = 0);
    ~rnWindow();
    void shakeWindow();

private:
    Ui::rnWindow *ui;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent * event);
    bool shouldMove = false;
    QPoint formerMainPos;
    QPoint formerMousePos;
signals:
    void emlit(QString);
private slots:
    void on_cancelBut_clicked();
    void on_appluBut_clicked();
};

#endif // RNWINDOW_H
