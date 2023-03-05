/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label_title;
    QLabel *label_user;
    QLabel *label_pw;
    QLineEdit *lineEdit_user;
    QLineEdit *lineEdit_pw;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_quit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1084, 764);
        label_title = new QLabel(Widget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setGeometry(QRect(91, 461, 16, 19));
        label_user = new QLabel(Widget);
        label_user->setObjectName(QString::fromUtf8("label_user"));
        label_user->setGeometry(QRect(377, 461, 30, 20));
        label_pw = new QLabel(Widget);
        label_pw->setObjectName(QString::fromUtf8("label_pw"));
        label_pw->setGeometry(QRect(377, 725, 30, 20));
        lineEdit_user = new QLineEdit(Widget);
        lineEdit_user->setObjectName(QString::fromUtf8("lineEdit_user"));
        lineEdit_user->setGeometry(QRect(450, 260, 142, 27));
        lineEdit_pw = new QLineEdit(Widget);
        lineEdit_pw->setObjectName(QString::fromUtf8("lineEdit_pw"));
        lineEdit_pw->setGeometry(QRect(664, 725, 142, 27));
        pushButton_ok = new QPushButton(Widget);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(664, 989, 80, 29));
        pushButton_quit = new QPushButton(Widget);
        pushButton_quit->setObjectName(QString::fromUtf8("pushButton_quit"));
        pushButton_quit->setGeometry(QRect(950, 989, 93, 29));

        retranslateUi(Widget);
        QObject::connect(pushButton_quit, &QPushButton::clicked, Widget, qOverload<>(&QWidget::close));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_title->setText(QString());
        label_user->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267", nullptr));
        label_pw->setText(QCoreApplication::translate("Widget", "\345\257\206\347\240\201", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("Widget", "ok", nullptr));
        pushButton_quit->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
