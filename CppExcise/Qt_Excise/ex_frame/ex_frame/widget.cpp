#include "widget.h"
#include "./ui_widget.h"
#include <QGridLayout>
#include <QIcon>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    this->setLayout(ui->gridLayout);
//    ui->label_title->setPixmap(QPixmap("qrc:/gensinImpact1.jpg"));
}

Widget::~Widget()
{
    delete ui;
}

