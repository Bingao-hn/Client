#include "Client.h"
#include "ui_Client.h"
#include "CameraSet.h"
#include "Connect.h"
#include <QTcpSocket>
#include <QDebug>

extern QTcpSocket* _socket;

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    _socket = new QTcpSocket(this);
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}

void Client::on_mCameraSet_triggered()
{
    CameraSet camset(this);
    camset.exec();
}

void Client::on_mConnect_triggered()
{
    Connect con(this);
    con.exec();
}
