/********************************************************************************
** Form generated from reading UI file 'createdb.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEDB_H
#define UI_CREATEDB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_createDB
{
public:
    QLineEdit *dbName;
    QPushButton *pushButton;
    QPushButton *closeBut;

    void setupUi(QWidget *createDB)
    {
        if (createDB->objectName().isEmpty())
            createDB->setObjectName(QStringLiteral("createDB"));
        createDB->resize(400, 180);
        dbName = new QLineEdit(createDB);
        dbName->setObjectName(QStringLiteral("dbName"));
        dbName->setGeometry(QRect(75, 60, 250, 30));
        pushButton = new QPushButton(createDB);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(115, 130, 170, 35));
        pushButton->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/createDB/jpg/resources/createDB.jpg)}\n"
"QPushButton:pressed{border-image: url(:/createDB/jpg/resources/createDB_press.jpg);} "));
        closeBut = new QPushButton(createDB);
        closeBut->setObjectName(QStringLiteral("closeBut"));
        closeBut->setGeometry(QRect(360, 0, 40, 30));
        closeBut->setStyleSheet(QStringLiteral("QPushButton{border-image:url(:/createDB/png/resources/closePNG.png);}"));

        retranslateUi(createDB);

        QMetaObject::connectSlotsByName(createDB);
    } // setupUi

    void retranslateUi(QWidget *createDB)
    {
        createDB->setWindowTitle(QApplication::translate("createDB", "Form", Q_NULLPTR));
        pushButton->setText(QString());
        closeBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class createDB: public Ui_createDB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEDB_H
