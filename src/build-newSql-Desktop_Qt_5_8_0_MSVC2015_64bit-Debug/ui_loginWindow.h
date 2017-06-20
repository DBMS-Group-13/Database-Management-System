/********************************************************************************
** Form generated from reading UI file 'loginWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginWindow
{
public:
    QLabel *backGround;
    QLabel *gifGround;
    QPushButton *closeBut;
    QLineEdit *idLine;
    QLineEdit *passwordLine;
    QPushButton *signBut;
    QCheckBox *remeberCheckBox;
    QCheckBox *autoCheckBox;
    QLabel *logoImg;
    QLabel *useridLabel;
    QLabel *passwordLabel;

    void setupUi(QWidget *loginWindow)
    {
        if (loginWindow->objectName().isEmpty())
            loginWindow->setObjectName(QStringLiteral("loginWindow"));
        loginWindow->resize(600, 500);
        backGround = new QLabel(loginWindow);
        backGround->setObjectName(QStringLiteral("backGround"));
        backGround->setGeometry(QRect(10, 10, 580, 480));
        backGround->setStyleSheet(QStringLiteral("background-color: rgb(235, 242, 249);"));
        gifGround = new QLabel(loginWindow);
        gifGround->setObjectName(QStringLiteral("gifGround"));
        gifGround->setGeometry(QRect(10, 10, 580, 240));
        closeBut = new QPushButton(loginWindow);
        closeBut->setObjectName(QStringLiteral("closeBut"));
        closeBut->setGeometry(QRect(550, 10, 40, 30));
        closeBut->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/login/button/resources/close.jpg);}\n"
"QPushButton:hover{border-image: url(:/login/button/resources/close_hover.jpg);}\n"
"QPushButton:pressed{border-image: url(:/login/button/resources/close_press.jpg);} "));
        idLine = new QLineEdit(loginWindow);
        idLine->setObjectName(QStringLiteral("idLine"));
        idLine->setGeometry(QRect(175, 280, 250, 51));
        passwordLine = new QLineEdit(loginWindow);
        passwordLine->setObjectName(QStringLiteral("passwordLine"));
        passwordLine->setGeometry(QRect(175, 331, 250, 51));
        signBut = new QPushButton(loginWindow);
        signBut->setObjectName(QStringLiteral("signBut"));
        signBut->setGeometry(QRect(175, 430, 250, 40));
        signBut->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/login/button/resources/sign.jpg)}\n"
"QPushButton:hover{border-image: url(:/login/button/resources/sign_hover.jpg);}\n"
"QPushButton:pressed{border-image: url(:/login/button/resources/sign_press.jpg);} "));
        remeberCheckBox = new QCheckBox(loginWindow);
        remeberCheckBox->setObjectName(QStringLiteral("remeberCheckBox"));
        remeberCheckBox->setGeometry(QRect(175, 400, 91, 19));
        autoCheckBox = new QCheckBox(loginWindow);
        autoCheckBox->setObjectName(QStringLiteral("autoCheckBox"));
        autoCheckBox->setGeometry(QRect(340, 400, 91, 19));
        logoImg = new QLabel(loginWindow);
        logoImg->setObjectName(QStringLiteral("logoImg"));
        logoImg->setGeometry(QRect(30, 80, 249, 131));
        logoImg->setStyleSheet(QStringLiteral("background-image: url(:/login/jpg/resources/logo.png);"));
        useridLabel = new QLabel(loginWindow);
        useridLabel->setObjectName(QStringLiteral("useridLabel"));
        useridLabel->setGeometry(QRect(100, 300, 72, 15));
        passwordLabel = new QLabel(loginWindow);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));
        passwordLabel->setGeometry(QRect(100, 350, 72, 15));

        retranslateUi(loginWindow);

        QMetaObject::connectSlotsByName(loginWindow);
    } // setupUi

    void retranslateUi(QWidget *loginWindow)
    {
        loginWindow->setWindowTitle(QApplication::translate("loginWindow", "Widget", Q_NULLPTR));
        backGround->setText(QString());
        gifGround->setText(QString());
        closeBut->setText(QString());
        signBut->setText(QString());
        remeberCheckBox->setText(QApplication::translate("loginWindow", "\350\256\260\344\275\217\345\257\206\347\240\201", Q_NULLPTR));
        autoCheckBox->setText(QApplication::translate("loginWindow", "\350\207\252\345\212\250\347\231\273\345\275\225", Q_NULLPTR));
        logoImg->setText(QString());
        useridLabel->setText(QApplication::translate("loginWindow", "\347\224\250\346\210\267\345\220\215:", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("loginWindow", "\345\257\206\347\240\201:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class loginWindow: public Ui_loginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
