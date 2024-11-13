#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client_simple;
    connect(client , &Client_simple::sig_recvInfoToUpdataUi,
            this , &MainWindow::slots_recvInfoToUpdataUi );
    if( client->clientSimpleStart() != 0){
        qDebug()<< "start err ! ";
    }else{
        qDebug()<< "start success ! ";
    }
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::slots_recvInfoToUpdataUi(char * s , int len ){
    QString str = "recv : " + QString::fromUtf8(s, len);
    ui->tb_recvInfo->append(str);
}

void MainWindow::on_pb_sendCmd_clicked()
{
    QString retstring = ui->te_inputCmd->toPlainText();
    ui->te_inputCmd->clear();
    ui->tb_recvInfo->append("send : " + retstring);
    //发送
    client->sendMessages(retstring.toStdString().c_str() , retstring.length());
}

