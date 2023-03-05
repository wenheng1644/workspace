#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->centralWidget()->setMouseTracking(true);
    this->setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    if(hasMouseTracking())
        std::cout << "yes" << std::endl;
    else
        std::cout << "no" << std::endl;



    QPushButton * m_push = new QPushButton("quit", this);
    m_push->setGeometry(50, 25, 100, 50);

//    m_push.setEnabled(true);
//    m_push.setCheckable(true);
    QObject::connect(m_push, &QPushButton::clicked, qApp, &QApplication::quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        qApp->quit();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();

    QString text = "坐标:" + QString::number(x) + "," + QString::number(y);
    this->statusBar()->showMessage(text);
}

