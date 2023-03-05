#include "widget.h"
#include "./ui_widget.h"
#include <QPlainTextEdit>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setLayout(ui->gridLayout);
    ui->gridLayout->addWidget(ui->label_title,0,1);
    ui->gridLayout->addWidget(ui->label_text,1,0);
    ui->gridLayout->addWidget(ui->pushButton_dir,1,1);
    ui->gridLayout->addWidget(ui->pushButton_check,1,2);
    ui->gridLayout->addWidget(ui->plainTextEdit_content, 2,0,1,3);

    ui->gridLayout->setRowStretch(0,2);
    ui->gridLayout->setRowStretch(1,2);
    ui->gridLayout->setRowStretch(2,4);

    ui->label_text->setText("路径:");
    ui->label_title->setText("文件助手");

    ui->pushButton_dir->setText("目录选择");
    ui->pushButton_check->setText("搜索");

    QObject::connect(ui->pushButton_dir, &QPushButton::clicked, this, &Widget::handle_pushButtonDir);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::handle_pushButtonDir()
{
    QString dirStr = QFileDialog::getExistingDirectory(this, "工作路径选择", QDir::rootPath());
    if(dirStr.isEmpty())
        return;

    qDebug() << "dirStr = " << dirStr;
    QDir dir;
    dir.setPath(dirStr);
    int fileCnt{};
    quint64 bytes = 0;
    forearchDir(dir, fileCnt, bytes);
}

void Widget::forearchDir(QDir dir, int &cnt, quint64 &bytes)
{
    dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);
    auto list = dir.entryInfoList();

    QString space(10, ' ');

    for(auto & info : list)
    {
        if(info.isDir())
        {
            QDir curDir;
            curDir.setPath(dir.path() + "\\" + info.fileName());
            forearchDir(curDir, cnt, bytes);
            continue;
        }

        ui->plainTextEdit_content->appendPlainText(QString("file name = %1%2size = %3bytes").arg(info.fileName(), 27).arg(space).arg(info.size()));
        cnt++;
        bytes += info.size();
    }
}

