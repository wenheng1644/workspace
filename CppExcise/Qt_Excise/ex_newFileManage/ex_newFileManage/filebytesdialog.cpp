#include "filebytesdialog.h"
#include "ui_filebytesdialog.h"

FileBytesDialog::FileBytesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileBytesDialog), m_curValue(0), m_curIndex(0)
{
    ui->setupUi(this);
    init();
}

FileBytesDialog::~FileBytesDialog()
{
    delete ui;
}

void FileBytesDialog::init()
{
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(1023);
    ui->spinBox->setValue(0);
//    ui->spinBox->setMinimumWidth(20);
//    ui->spinBox->setFixedWidth(40);

    ui->comboBox->addItems({"B", "KB", "MB", "GB"});
    ui->comboBox->setCurrentIndex(0);

    setWindowTitle("文件大小筛选");

}

void FileBytesDialog::on_buttonBox_accepted()
{
    m_curValue = ui->spinBox->value();
    m_curIndex = ui->comboBox->currentIndex();
}

