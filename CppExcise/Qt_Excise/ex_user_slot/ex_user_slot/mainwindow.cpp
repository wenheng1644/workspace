#include "mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_widget(new QWidget(this)),m_push(new QPushButton("push", m_widget)), m_cbox(new QCheckBox(m_widget)), m_lable(new QLabel(m_widget))
{
    m_lable->setText(QTime::currentTime().toString());
    m_cbox->setText("connect");
    setCentralWidget(m_widget);

    QHBoxLayout* layout = new QHBoxLayout(m_widget);
    layout->addWidget(m_push);
    layout->addWidget(m_cbox);
    layout->addWidget(m_lable);

    startTimer(1000);

    QObject::connect(m_cbox, &QCheckBox::stateChanged, this, &MainWindow::handle_check);

    dumpObjectTree();
}

MainWindow::~MainWindow()
{
}

void MainWindow::handle_check(int state)
{
    this->statusBar()->showMessage("");
    if(state == Qt::Checked)
        QObject::connect(m_push, &QPushButton::clicked, this, &MainWindow::handle_push);
    else
        QObject::disconnect(m_push, &QPushButton::clicked, this, &MainWindow::handle_push);
}

void MainWindow::handle_push()
{
    this->statusBar()->showMessage("is connect");
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    m_lable->setText(QTime::currentTime().toString());
}

