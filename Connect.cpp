#include "Connect.h"
#include "ui_Connect.h"
#include <QTcpSocket>
extern QTcpSocket* _socket;

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
    //建立连接
    QString ip = ui->ip->text();
    QString port = ui->port->text();
    _socket->connectToHost(ip, port.toInt());

    //发送一个消息，看是否有应答，有则建立成功
}

void Connect::on_pushButton_clicked()
{
    _socket->close();
}
