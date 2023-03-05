#include "widget.h"
#include <QIcon>
#include <QFile>
#include <QStyleOption>
#include <QPainter>

const QString g_resPath = "../../res";

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_lable(new QLabel("0", this))
{
    QPushButton * buttPlus = new QPushButton("+", this);
    QPushButton * buttMin = new QPushButton("-", this);

    QGridLayout * layout = new QGridLayout(this);

    layout->addWidget(buttPlus, 0, 0, 1, 1);
    layout->addWidget(buttMin, 0, 1, 1, 1);
    layout->addWidget(m_lable, 1, 0, 1, 2);

    setLayout(layout);

    m_lable->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QObject::connect(buttPlus, &QPushButton::clicked, this, &Widget::on_plus);
    QObject::connect(buttMin, &QPushButton::clicked, this, &Widget::on_min);

//    setAttribute(Qt::WA_StyledBackground);
    setIcon();
    setStyle();
}

Widget::~Widget()
{
}

void Widget::on_min()
{
    int v = m_lable->text().toInt();
    m_lable->setText(QString::number(--v));
}

void Widget::on_plus()
{
    int v = m_lable->text().toInt();
    m_lable->setText(QString::number(++v));
}

void Widget::setIcon()
{
    qDebug() << "path = " << g_resPath + "/images/gensinImpact1.jpg";
    this->setWindowIcon(QIcon(g_resPath + "/images/gensinImpact1.jpg"));
}

void Widget::setStyle()
{
    QFile f(g_resPath + "/uiStyle/style1.css");
    if(!f.exists())
    {
        qDebug() << "f is not exist";
        return;
    }

    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug() << "open error";
        return;
    }
//    qDebug() << QString::fromLatin1(f.readAll());
    this->setStyleSheet(QString::fromLatin1(f.readAll()));

}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

