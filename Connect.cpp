#include "Connect.h"
#include "ui_Connect.h"
#include <QTcpSocket>
extern QString serverIp;

Connect::Connect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connect)
{
    ui->setupUi(this);
}

Connect::~Connect()
{
    delete ui;
}

void Connect::on_pBtn_connect_clicked()
{
    //设置参数
    serverIp = ui->ip->text();
    QString port = ui->port->text();
//    _socket->connectToHost(ip, port.toInt());
    this->close();
    //发送一个消息，看是否有应答，有则建立成功
}


