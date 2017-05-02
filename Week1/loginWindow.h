#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {
class loginWindow;
}

class loginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit loginWindow(QWidget *parent = 0);
    ~loginWindow();
    QString getUserid();

private slots:
    void on_closeBut_clicked();

    void on_signBut_clicked();

private:
    Ui::loginWindow *ui;
    void paintEvent(QPaintEvent *event);

    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent * event);

    bool shouldMove = false;
    QPoint formerMainPos;
    QPoint formerMousePos;
};

#endif // LOGINWINDOW_H
