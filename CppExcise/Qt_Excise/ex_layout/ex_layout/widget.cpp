#include "widget.h"
#include "./ui_widget.h"

#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QPushButton * btt1 = new QPushButton("按钮1", this);
//    QPushButton * btt2 = new QPushButton("按钮2", this);
//    QPushButton * btt3 = new QPushButton("按钮3", this);

//    QVBoxLayout * vLayout = new QVBoxLayout(this);

//    vLayout->addWidget(btt1);
//    vLayout->addWidget(btt2);
//    vLayout->addWidget(btt3);

//    btt1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    btt2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    btt3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

//    QPushButton * buttok = new QPushButton("ok", this);
//    QPushButton * buttapp = new QPushButton("apply", this);
//    QPushButton * butttemp = new QPushButton("temp", this);

//    QVBoxLayout * mainLayout = new QVBoxLayout(this);
//    QHBoxLayout * hlayout = new QHBoxLayout();


//    hlayout->addWidget(butttemp, 1);
//    hlayout->addWidget(buttok, 1, Qt::AlignRight);
//    hlayout->addWidget(buttapp);


//    mainLayout->addStretch(1);
//    mainLayout->addLayout(hlayout);


    QPushButton * buttadd = new QPushButton("add", this);
    QPushButton * buttdel = new QPushButton("del", this);
    QPushButton * buttrename = new QPushButton("rename", this);
    QPushButton * buttquit = new QPushButton("quit", this);

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    QVBoxLayout * layout = new QVBoxLayout(this);

    layout->addStretch(1);
    layout->addSpacing(7);
    layout->addWidget(buttadd);
    layout->addWidget(buttdel);
    layout->addWidget(buttrename);
    layout->addWidget(buttquit);
    layout->addStretch(1);

    QListWidget * list = new QListWidget(this);
    list->addItem("徐伟镇");
    list->addItem("邝慧娴");

    mainLayout->addWidget(list);
//    mainLayout->addStretch(1);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(layout);


}

Widget::~Widget()
{
    delete ui;
}

