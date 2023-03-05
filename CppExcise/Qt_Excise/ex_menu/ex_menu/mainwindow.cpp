#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_labelTime(new QLabel("", this)), m_viewStautsBar(new QAction("viewStautsBar", this))
{
    QAction * quit = new QAction("&Quit", this);
    m_viewStautsBar->setCheckable(true);
    m_viewStautsBar->setChecked(false);
    QMenu* menu = menuBar()->addMenu("&File");

    quit->setShortcut(tr("CTRL+Q"));
    menu->addAction(quit);
    menu->addAction(m_viewStautsBar);

    QObject::connect(quit, &QAction::triggered, qApp, &QApplication::quit);

    QToolBar* tool = addToolBar("tool");
    tool->addAction(quit);



    QObject::connect(m_viewStautsBar, &QAction::triggered, this, &MainWindow::on_statusBar);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_statusBar()
{
    if(m_viewStautsBar->isChecked())
    {
//        statusBar()->showMessage(QTime::currentTime().toString());
        startTimer(1000);
        statusBar()->show();
    }
    else
    {

        statusBar()->hide();
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(m_viewStautsBar->isChecked())
        statusBar()->setStatusTip(QTime::currentTime().toString());
}

