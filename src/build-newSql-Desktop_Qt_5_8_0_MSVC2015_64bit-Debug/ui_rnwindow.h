/********************************************************************************
** Form generated from reading UI file 'rnwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RNWINDOW_H
#define UI_RNWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_rnWindow
{
public:
    QPushButton *appluBut;
    QLineEdit *lineEdit;
    QPushButton *cancelBut;

    void setupUi(QDialog *rnWindow)
    {
        if (rnWindow->objectName().isEmpty())
            rnWindow->setObjectName(QStringLiteral("rnWindow"));
        rnWindow->resize(400, 180);
        appluBut = new QPushButton(rnWindow);
        appluBut->setObjectName(QStringLiteral("appluBut"));
        appluBut->setGeometry(QRect(200, 130, 170, 35));
        appluBut->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/recordwidget/jpg/resources/apply.jpg)}\n"
"QPushButton:pressed{border-image: url(:/recordwidget/jpg/resources/apply_pressed.jpg);} "));
        lineEdit = new QLineEdit(rnWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(70, 50, 271, 31));
        cancelBut = new QPushButton(rnWindow);
        cancelBut->setObjectName(QStringLiteral("cancelBut"));
        cancelBut->setGeometry(QRect(30, 130, 170, 35));
        cancelBut->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/recordwidget/jpg/resources/cencel.jpg)}\n"
"QPushButton:pressed{border-image: url(:/recordwidget/jpg/resources/cencel_pressed.jpg);} "));

        retranslateUi(rnWindow);

        QMetaObject::connectSlotsByName(rnWindow);
    } // setupUi

    void retranslateUi(QDialog *rnWindow)
    {
        rnWindow->setWindowTitle(QApplication::translate("rnWindow", "Dialog", Q_NULLPTR));
        appluBut->setText(QString());
        cancelBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class rnWindow: public Ui_rnWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RNWINDOW_H
