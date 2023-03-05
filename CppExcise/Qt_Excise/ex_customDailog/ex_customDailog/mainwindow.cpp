#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <QSharedPointer>
#include <QTextCursor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->tabWidget->setTabsClosable(true);
    QObject::connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this,
                     [=](int index){ ui->tabWidget->removeTab(index);});
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}


void MainWindow::on_actionNew_triggered()
{
    int lastIndex = ui->tabWidget->count();
    QSharedPointer<QTextEdit> ptr(new QTextEdit(this));
    QTextEdit * ptr2 = new QTextEdit(this);
    int index = ui->tabWidget->insertTab(lastIndex, ptr2, QString("item") + QString::number(lastIndex+1));
    ui->tabWidget->setCurrentIndex(index);

    QTextCursor cursor(ptr2->textCursor());
    cursor.movePosition(QTextCursor::End);
    cursor.insertText("hello\nworld");
    cursor.movePosition(QTextCursor::Start);
    cursor.insertText("what?");
}

