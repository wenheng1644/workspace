#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    void handle_pushButtonDir();
    void forearchDir(QDir dir, int& cnt, quint64 & bytes);
};
#endif // WIDGET_H
