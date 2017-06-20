/********************************************************************************
** Form generated from reading UI file 'createtable.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETABLE_H
#define UI_CREATETABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_createTable
{
public:
    QPushButton *closeBut;
    QLineEdit *dbName;
    QLineEdit *tableName;
    QPushButton *pushButton;
    QTableView *tableView;
    QPushButton *flashButton;
    QProgressBar *pBar;

    void setupUi(QWidget *createTable)
    {
        if (createTable->objectName().isEmpty())
            createTable->setObjectName(QStringLiteral("createTable"));
        createTable->resize(1000, 600);
        closeBut = new QPushButton(createTable);
        closeBut->setObjectName(QStringLiteral("closeBut"));
        closeBut->setGeometry(QRect(960, 0, 40, 30));
        closeBut->setStyleSheet(QStringLiteral("QPushButton{border-image:url(:/createDB/png/resources/closePNG.png);}"));
        dbName = new QLineEdit(createTable);
        dbName->setObjectName(QStringLiteral("dbName"));
        dbName->setGeometry(QRect(60, 45, 250, 30));
        tableName = new QLineEdit(createTable);
        tableName->setObjectName(QStringLiteral("tableName"));
        tableName->setGeometry(QRect(330, 45, 250, 30));
        pushButton = new QPushButton(createTable);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(400, 550, 170, 35));
        pushButton->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/createtable/jpg/resources/createTable.jpg)}\n"
"QPushButton:pressed{border-image: url(:/createtable/jpg/resources/createTable_pressed.jpg)} "));
        tableView = new QTableView(createTable);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(60, 90, 880, 400));
        flashButton = new QPushButton(createTable);
        flashButton->setObjectName(QStringLiteral("flashButton"));
        flashButton->setGeometry(QRect(600, 45, 40, 30));
        flashButton->setStyleSheet(QStringLiteral("QPushButton{border-image:url(:/createtable/png/resources/reflash.png)}"));
        pBar = new QProgressBar(createTable);
        pBar->setObjectName(QStringLiteral("pBar"));
        pBar->setGeometry(QRect(660, 60, 281, 23));
        pBar->setStyleSheet(QLatin1String("QProgressBar{\n"
"        border: none;\n"
"        color: white;\n"
"        text-align: center;\n"
"        background: rgb(68, 69, 73);\n"
"}\n"
"QProgressBar::chunk {\n"
"        border: none;\n"
"        background: rgb(0, 160, 230);\n"
"}"));
        pBar->setValue(0);

        retranslateUi(createTable);

        QMetaObject::connectSlotsByName(createTable);
    } // setupUi

    void retranslateUi(QWidget *createTable)
    {
        createTable->setWindowTitle(QApplication::translate("createTable", "Form", Q_NULLPTR));
        closeBut->setText(QString());
        pushButton->setText(QString());
        flashButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class createTable: public Ui_createTable {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETABLE_H
