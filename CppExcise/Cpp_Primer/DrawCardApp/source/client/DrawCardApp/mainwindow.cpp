#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QIcon>
#include <QDir>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),m_titleName("抽卡模拟器"),m_signlePushName("单抽"),m_tenPushName("十连抽"),m_helpIcon("帮助"),m_draw()
    , m_isLog(false)
{
    ui->setupUi(this);
    ui->u_title->setText(QString(m_titleName.data()));
    ui->u_signlePushButton->setText(QString(m_signlePushName.data()));
    ui->u_tenPushButton->setText(QString(m_tenPushName.data()));
    ui->u_helpPushButton->setText(QString());

    QIcon help_icon(".\\comm\\pictrue\\help.png");
    ui->u_helpPushButton->setIcon(help_icon);
    ui->u_helpPushButton->setIconSize(QSize(50,50));
//    ui->u_helpPushButton->setFlat(true);
    ui->u_helpPushButton->setStyleSheet("background-color:transparent");
    ui->u_helpPushButton->setFocusPolicy(Qt::NoFocus);

    ui->menubar->adjustSize();
    ui->menu->addAction(ui->action_clear);
    ui->menu->addAction(ui->action_log);

    ui->menubar->addSeparator();
    ui->menubar->addAction(ui->action_help);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_u_signlePushButton_clicked()
{
    vector<drawcard_data> res = m_draw.singleGet(m_isLog);
    writeDrawDataToEditor(res);
}

void MainWindow::on_u_tenPushButton_clicked()
{
    vector<drawcard_data> res = m_draw.tenGet(m_isLog);
    writeDrawDataToEditor(res);
}

void MainWindow::writeDrawDataToEditor(vector<drawcard_data> &result)
{
    for(auto& draw_result : result)
    {
        QString lineData = m_draw.getDrawResultInfo(draw_result).data();
        ui->resultTextEdit->append(lineData);
    }
}

void MainWindow::on_action_clear_triggered()
{
    ui->resultTextEdit->clear();
}

void MainWindow::on_u_helpPushButton_clicked()
{
    QMessageBox::information(this,"帮助","这是一个抽卡模拟器\n允许单抽或十连");
}

void MainWindow::on_action_log_triggered(bool checked)
{
    m_isLog = checked;
}
