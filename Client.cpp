#include "Client.h"
#include "ui_Client.h"
//#include "CameraSet.h"
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

    camset = new CameraSet();
    camauto = new CameraAuto();

    connect(camset,SIGNAL(close_signal()),
            this,SLOT(close_slot()));
    connect(camauto,SIGNAL(close_signal()),
            this,SLOT(close_slot()));
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

void Client::on_btn_manual_clicked()
{
    this->hide();
    camset->show();
}

void Client::close_slot()
{
    this->show();
}

void Client::on_btn_auto_clicked()
{
    this->hide();
    camauto->show();
}
