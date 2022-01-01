#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <vector>
#include "server/drawCard/draw.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_u_signlePushButton_clicked();

    void on_u_tenPushButton_clicked();

    void on_action_clear_triggered();

    void on_u_helpPushButton_clicked();

private:
    Ui::MainWindow *ui;

    string m_titleName;
    string m_signlePushName;
    string m_tenPushName;
    string m_helpIcon;

    draw m_draw;


    //将数据写入到编辑显示器中
    void writeDrawDataToEditor(vector<drawcard_data>& result);

};
#endif // MAINWINDOW_H
