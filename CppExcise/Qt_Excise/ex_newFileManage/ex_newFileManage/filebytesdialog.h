#ifndef FILEBYTESDIALOG_H
#define FILEBYTESDIALOG_H

#include <QDialog>

namespace Ui {
class FileBytesDialog;
}

class FileBytesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileBytesDialog(QWidget *parent = nullptr);
    ~FileBytesDialog();

    quint64 value() { return m_curValue;}
    int index() {return m_curIndex;}

private slots:
    void on_buttonBox_accepted();

private:
    void init();
private:
    Ui::FileBytesDialog *ui;

    quint64 m_curValue;
    int m_curIndex;
};

#endif // FILEBYTESDIALOG_H
