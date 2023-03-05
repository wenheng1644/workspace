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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_title;
    QPushButton *pushButton_check;
    QPushButton *pushButton_dir;
    QLabel *label_text;
    QPlainTextEdit *plainTextEdit_content;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 600);
        gridLayoutWidget = new QWidget(Widget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(330, 130, 269, 150));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_title = new QLabel(gridLayoutWidget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_title, 0, 1, 1, 1);

        pushButton_check = new QPushButton(gridLayoutWidget);
        pushButton_check->setObjectName(QString::fromUtf8("pushButton_check"));

        gridLayout->addWidget(pushButton_check, 2, 2, 1, 1);

        pushButton_dir = new QPushButton(gridLayoutWidget);
        pushButton_dir->setObjectName(QString::fromUtf8("pushButton_dir"));

        gridLayout->addWidget(pushButton_dir, 2, 1, 1, 1);

        label_text = new QLabel(gridLayoutWidget);
        label_text->setObjectName(QString::fromUtf8("label_text"));
        label_text->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_text, 2, 0, 1, 1);

        plainTextEdit_content = new QPlainTextEdit(Widget);
        plainTextEdit_content->setObjectName(QString::fromUtf8("plainTextEdit_content"));
        plainTextEdit_content->setGeometry(QRect(360, 380, 104, 85));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label_title->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        pushButton_check->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        pushButton_dir->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        label_text->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
