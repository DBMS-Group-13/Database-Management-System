/********************************************************************************
** Form generated from reading UI file 'recordwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDWIDGET_H
#define UI_RECORDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecordWidget
{
public:
    QLabel *nameLabel;
    QPushButton *pushButton;
    QTableView *tableView;
    QPushButton *applyButton;
    QPushButton *cencelButton;

    void setupUi(QWidget *RecordWidget)
    {
        if (RecordWidget->objectName().isEmpty())
            RecordWidget->setObjectName(QStringLiteral("RecordWidget"));
        RecordWidget->resize(800, 650);
        nameLabel = new QLabel(RecordWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setGeometry(QRect(10, 0, 161, 31));
        nameLabel->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\271\274\345\234\206\" ;\n"
"color: rgb(255, 255, 255);"));
        pushButton = new QPushButton(RecordWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(765, 0, 35, 30));
        pushButton->setStyleSheet(QStringLiteral("QPushButton{border-image:url(:/createDB/png/resources/closePNG.png);}"));
        tableView = new QTableView(RecordWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(0, 40, 800, 560));
        tableView->setStyleSheet(QStringLiteral(""));
        applyButton = new QPushButton(RecordWidget);
        applyButton->setObjectName(QStringLiteral("applyButton"));
        applyButton->setGeometry(QRect(639, 610, 131, 30));
        applyButton->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/recordwidget/jpg/resources/apply.jpg)}\n"
"QPushButton:pressed{border-image: url(:/recordwidget/jpg/resources/apply_pressed.jpg);} "));
        cencelButton = new QPushButton(RecordWidget);
        cencelButton->setObjectName(QStringLiteral("cencelButton"));
        cencelButton->setGeometry(QRect(500, 610, 120, 30));
        cencelButton->setStyleSheet(QLatin1String("QPushButton{border-image:url(:/recordwidget/jpg/resources/cencel.jpg)}\n"
"QPushButton:pressed{border-image: url(:/recordwidget/jpg/resources/cencel_pressed.jpg);} "));
        tableView->raise();
        nameLabel->raise();
        pushButton->raise();
        applyButton->raise();
        cencelButton->raise();

        retranslateUi(RecordWidget);

        QMetaObject::connectSlotsByName(RecordWidget);
    } // setupUi

    void retranslateUi(QWidget *RecordWidget)
    {
        RecordWidget->setWindowTitle(QApplication::translate("RecordWidget", "Form", Q_NULLPTR));
        nameLabel->setText(QString());
        pushButton->setText(QString());
        applyButton->setText(QString());
        cencelButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RecordWidget: public Ui_RecordWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDWIDGET_H
