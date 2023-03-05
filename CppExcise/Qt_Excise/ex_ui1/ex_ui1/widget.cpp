#include "widget.h"
#include <QGridLayout>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFrame * frame1 = new QFrame(this);
    frame1->setFrameStyle(QFrame::Box);
    frame1->setCursor(Qt::SizeAllCursor);

    QFrame * frame2 = new QFrame(this);
    frame2->setFrameStyle(QFrame::Panel);
    frame2->setCursor(Qt::WaitCursor);

    QFrame * frame3 = new QFrame(this);
    frame3->setFrameStyle(QFrame::WinPanel);
    frame3->setCursor(Qt::BlankCursor);

    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(frame1, 0, 0);
    layout->addWidget(frame2, 0, 1);
    layout->addWidget(frame3, 0, 2);

    setLayout(layout);
    layout->setColumnStretch(0,1);
    layout->setColumnStretch(1,1);
    layout->setColumnStretch(2,1);

    QGridLayout * lay2 = new QGridLayout(frame2);
    QPushButton * butt = new QPushButton("quit",this);
    lay2->addWidget(butt,0,0);

    QObject::connect(butt, &QPushButton::clicked, qApp, &QApplication::quit);

    QLineEdit * line1 = new QLineEdit("line1", this);
    QLineEdit * line2 = new QLineEdit("line2", this);

    lay2->addWidget(line1, 1,0);
    lay2->addWidget(line2, 2,0);

    line2->setObjectName("sobj");

}

Widget::~Widget()
{
}

