#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QFileSystemModel>

#include <filesizefilter.h>
#include "filebytesdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

const int Kbytes = 1024;
const int Mbytes = pow(Kbytes, 2);
const quint64 Gbytes = Mbytes * Kbytes;

class Widget : public QWidget
{
    Q_OBJECT
public:
    using FileInfoListType = QList<QPair<QString, quint64>>;

    static QString transFromBytes(quint64 bytes);
    static quint64 transFromFormatBytes(quint64 value, int index);
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_pushButton_rootPath_clicked();

    void on_pushButton_ok_clicked();

private:
    void init();
    void search(QDir& dir, const quint64& minBytes, FileInfoListType& res);
    void test();

    void _thread(QDir dir, quint64 bytes, QString path);
private:
    Ui::Widget *ui;
    QFileSystemModel* m_model;
    FileSizeFilter* m_filter;
    FileBytesDialog* m_dialg;
};
#endif // WIDGET_H
