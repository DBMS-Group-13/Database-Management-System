/********************************************************************************
** Form generated from reading UI file 'centerwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CENTERWINDOW_H
#define UI_CENTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_centerwindow
{
public:
    QLabel *background;
    QLabel *title;
    QPushButton *close;
    QLabel *status;
    QTreeView *treeview;
    QLabel *label;
    QPushButton *creDBBut;
    QPushButton *dropDBBut;
    QPushButton *addTableBut;
    QPushButton *delTableBut;
    QTableView *tableView;
    QPushButton *pushButton;

    void setupUi(QWidget *centerwindow)
    {
        if (centerwindow->objectName().isEmpty())
            centerwindow->setObjectName(QStringLiteral("centerwindow"));
        centerwindow->resize(1600, 800);
        background = new QLabel(centerwindow);
        background->setObjectName(QStringLiteral("background"));
        background->setGeometry(QRect(10, 10, 1580, 780));
        background->setStyleSheet(QStringLiteral("background-color: rgb(235, 242, 249);"));
        title = new QLabel(centerwindow);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(10, 10, 1580, 180));
        title->setStyleSheet(QStringLiteral("border-image: url(:/mainWindow/jpg/resources/mainTitle.jpg);"));
        close = new QPushButton(centerwindow);
        close->setObjectName(QStringLiteral("close"));
        close->setGeometry(QRect(1550, 10, 40, 30));
        close->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/mainWindow/jpg/resources/closeCenter.jpg)}\n"
"QPushButton:hover{border-image: url(:/login/button/resources/close_hover.jpg);}\n"
"QPushButton:pressed{border-image: url(:/login/button/resources/close_press.jpg);} "));
        status = new QLabel(centerwindow);
        status->setObjectName(QStringLiteral("status"));
        status->setGeometry(QRect(10, 760, 1580, 30));
        status->setStyleSheet(QStringLiteral("border-image: url(:/mainWindow/jpg/resources/status.jpg);"));
        status->setTextFormat(Qt::AutoText);
        treeview = new QTreeView(centerwindow);
        treeview->setObjectName(QStringLiteral("treeview"));
        treeview->setGeometry(QRect(10, 190, 260, 570));
        treeview->setStyleSheet(QString::fromUtf8("QTreeView {\n"
"	border-image: url(:/mainWindow/jpg/resources/boT.jpg);\n"
"	background-color: rgb(255, 255, 255);\n"
"    show-decoration-selected: 1;\n"
"	\n"
"	font: 10pt \"\345\271\274\345\234\206\";\n"
"}\n"
"QTreeView::item {\n"
"    border: 1px solid #d9d9d9;\n"
"    border-top-color: transparent;\n"
"    border-bottom-color: transparent;\n"
"}\n"
"\n"
"QTreeView::item:hover {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);\n"
"    border: 1px solid #bfcde4;\n"
"}\n"
"\n"
"QTreeView::item:selected {\n"
"    border: 1px solid #567dbc;\n"
"}\n"
"\n"
"QTreeView::item:selected:active{\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);\n"
"}\n"
"\n"
"QTreeView::item:selected:!active {\n"
"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6b9be8, stop: 1 #577fbf);\n"
"}\n"
"\n"
"QTreeView::branch:has-siblings:!adjoins-item {\n"
"    border-image: url(:/mainWindow/png/resources/vline.png) 0;\n"
""
                        "}\n"
"\n"
"QTreeView::branch:has-siblings:adjoins-item {\n"
"    border-image: url(:/mainWindow/png/resources/branch-more.png) 0;\n"
"}\n"
"\n"
"QTreeView::branch:!has-children:!has-siblings:adjoins-item {\n"
"    border-image: url(:/mainWindow/png/resources/branch-end.png) 0;\n"
"}\n"
"\n"
"QTreeView::branch:has-children:!has-siblings:closed,\n"
"QTreeView::branch:closed:has-children:has-siblings {\n"
"    border-image: none;\n"
"    image: url(:/mainWindow/png/resources/branch-closed.png);\n"
"}\n"
"\n"
"QTreeView::branch:open:has-children:!has-siblings,\n"
"QTreeView::branch:open:has-children:has-siblings  {\n"
"    border-image: none;\n"
"    image: url(:/mainWindow/png/resources/branch-open.png);\n"
"}"));
        label = new QLabel(centerwindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 221, 21));
        label->setStyleSheet(QStringLiteral("border-image: url(:/mainWindow/png/resources/titleText.png);"));
        creDBBut = new QPushButton(centerwindow);
        creDBBut->setObjectName(QStringLiteral("creDBBut"));
        creDBBut->setGeometry(QRect(40, 70, 100, 100));
        creDBBut->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/mainWindow/png/resources/open.png);}\n"
"QPushButton:hover{border-image:url(:/mainWindow/png/resources/open_hover.png);}"));
        dropDBBut = new QPushButton(centerwindow);
        dropDBBut->setObjectName(QStringLiteral("dropDBBut"));
        dropDBBut->setGeometry(QRect(160, 70, 100, 100));
        dropDBBut->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/mainWindow/png/resources/create.png);}\n"
"QPushButton:hover{border-image:url(:/mainWindow/png/resources/create_hover.png);}"));
        addTableBut = new QPushButton(centerwindow);
        addTableBut->setObjectName(QStringLiteral("addTableBut"));
        addTableBut->setGeometry(QRect(280, 70, 100, 100));
        addTableBut->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/mainWindow/png/resources/addTable.png)}\n"
"QPushButton:hover{border-image:url(:/mainWindow/png/resources/addTable_hover.png)}"));
        delTableBut = new QPushButton(centerwindow);
        delTableBut->setObjectName(QStringLiteral("delTableBut"));
        delTableBut->setGeometry(QRect(400, 70, 100, 100));
        delTableBut->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/mainWindow/png/resources/delTable.png)}\n"
"QPushButton:hover{border-image:url(:/mainWindow/png/resources/delTable_hover.png)}\n"
""));
        tableView = new QTableView(centerwindow);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(270, 190, 1320, 570));
        tableView->setStyleSheet(QString::fromUtf8("    QTableView{  \n"
"	background-image: url(:/mainWindow/jpg/resources/boT.jpg);\n"
"        color: rgb(0, 0, 0);  \n"
"        border: 1px solid rgb(175, 167, 179);          /*\350\276\271\346\241\206\351\242\234\350\211\262*/  \n"
"        gridline-color:#C07010;             /*grid\347\272\277\351\242\234\350\211\262*/  \n"
"        background-color: rgb(240, 240, 240);  \n"
"        alternate-background-color: rgb(200, 200, 200); /*\350\241\214\344\272\244\346\233\277\351\242\234\350\211\262*/  \n"
"        selection-background-color: rgb(130, 190, 100); /*\351\200\211\344\270\255\350\241\214\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    }  \n"
"      \n"
"    QTableView::item:!alternate:!selected{  \n"
"        background-color: rgb(220, 220, 220);    /*\344\272\244\346\233\277\350\241\214\347\232\204\345\217\246\344\270\200\351\242\234\350\211\262*/  \n"
"    }  "));
        pushButton = new QPushButton(centerwindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1370, 10, 180, 180));
        pushButton->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/mainWindow/png/resources/log.png)}\n"
"QPushButton:hover{border-image:url(:/mainWindow/png/resources/log_hover.png)}\n"
""));

        retranslateUi(centerwindow);

        QMetaObject::connectSlotsByName(centerwindow);
    } // setupUi

    void retranslateUi(QWidget *centerwindow)
    {
        centerwindow->setWindowTitle(QApplication::translate("centerwindow", "Form", Q_NULLPTR));
        background->setText(QString());
        title->setText(QString());
        close->setText(QString());
        status->setText(QString());
        label->setText(QString());
        creDBBut->setText(QString());
        dropDBBut->setText(QString());
        addTableBut->setText(QString());
        delTableBut->setText(QString());
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class centerwindow: public Ui_centerwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CENTERWINDOW_H
