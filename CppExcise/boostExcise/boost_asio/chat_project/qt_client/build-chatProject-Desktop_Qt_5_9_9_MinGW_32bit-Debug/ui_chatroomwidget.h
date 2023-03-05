/********************************************************************************
** Form generated from reading UI file 'chatroomwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOMWIDGET_H
#define UI_CHATROOMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatRoomWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit_msg;
    QSpacerItem *verticalSpacer;
    QTextEdit *textEdit_content;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_help;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *chatRoomWidget)
    {
        if (chatRoomWidget->objectName().isEmpty())
            chatRoomWidget->setObjectName(QStringLiteral("chatRoomWidget"));
        chatRoomWidget->resize(770, 573);
        horizontalLayout_2 = new QHBoxLayout(chatRoomWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        listWidget = new QListWidget(chatRoomWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        horizontalLayout->addWidget(listWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEdit_msg = new QTextEdit(chatRoomWidget);
        textEdit_msg->setObjectName(QStringLiteral("textEdit_msg"));

        verticalLayout->addWidget(textEdit_msg);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        textEdit_content = new QTextEdit(chatRoomWidget);
        textEdit_content->setObjectName(QStringLiteral("textEdit_content"));

        verticalLayout->addWidget(textEdit_content);

        verticalLayout->setStretch(0, 8);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 2);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        pushButton_help = new QPushButton(chatRoomWidget);
        pushButton_help->setObjectName(QStringLiteral("pushButton_help"));

        verticalLayout_2->addWidget(pushButton_help);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 8);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);
        horizontalLayout->setStretch(2, 10);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);

        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(chatRoomWidget);

        QMetaObject::connectSlotsByName(chatRoomWidget);
    } // setupUi

    void retranslateUi(QWidget *chatRoomWidget)
    {
        chatRoomWidget->setWindowTitle(QApplication::translate("chatRoomWidget", "Form", Q_NULLPTR));
        pushButton_help->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class chatRoomWidget: public Ui_chatRoomWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOMWIDGET_H
