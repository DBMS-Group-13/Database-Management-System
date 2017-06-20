#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include <QWidget>

namespace Ui {
class centerwindow;
}

class centerwindow : public QWidget
{
    Q_OBJECT

public:
    explicit centerwindow(QWidget *parent = 0, QString userid = "asas");
    ~centerwindow();

private slots:
    void on_pushButton_clicked();
    void on_close_clicked();

private:
    Ui::centerwindow *ui;
    void paintEvent(QPaintEvent *event);
    void initTree();
    void initStatus(QString userid);


    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent (QMouseEvent * event);

    bool shouldMove = false;
    QPoint formerMainPos;
    QPoint formerMousePos;
};

#endif // CENTERWINDOW_H
