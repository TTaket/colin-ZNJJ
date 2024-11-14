#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../client_simple/client_simple.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_sendCmd_clicked();
    void slots_recvInfoToUpdataUi(char * s , int len );

    void on_pb_cmd1_clicked();

    void on_pb_cmd2_clicked();

private:
    Client_simple *client;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
