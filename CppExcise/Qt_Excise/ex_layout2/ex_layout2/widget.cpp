#include "widget.h"
#include "./ui_widget.h"

#include <QtWidgets>
#include <QSizePolicy>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QFormLayout * formlayout = new QFormLayout(this);
//    QLineEdit * line1 = new QLineEdit(this);
//    QLineEdit * line2 = new QLineEdit(this);
//    QLineEdit * line3 = new QLineEdit(this);

//    formlayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    formlayout->addRow("Name", line1);
//    formlayout->addRow("Email", line2);
//    formlayout->addRow("Age", line3);

    QLabel * lab1 = new QLabel("Name", this);
    QLabel * lab2 = new QLabel("Age", this);
    QLabel * lab3 = new QLabel("Text", this);

    QLineEdit * line1 = new QLineEdit(this);
    QLineEdit * line2 = new QLineEdit(this);
    QTextEdit * text1 = new QTextEdit(this);



    QGridLayout * layout = new QGridLayout(this);

    layout->addWidget(lab1, 0,0, 1,1, Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(lab2, 1,0, 1,1, Qt::AlignRight | Qt::AlignVCenter);
    layout->addWidget(lab3, 2,0, 1,1, Qt::AlignRight | Qt::AlignTop);

    layout->addWidget(line1, 0,1, 1,1);
    layout->addWidget(line2, 1,1, 1,1);

    layout->addWidget(text1, 2,1, 3,1);
    text1->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);

}

Widget::~Widget()
{
    delete ui;
}

