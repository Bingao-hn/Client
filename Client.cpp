#include "Client.h"
#include "ui_Client.h"
//#include "CameraSet.h"
#include "Connect.h"
#include <QTcpSocket>
#include <QDebug>

extern QString serverIp;

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    Connect con(this);
    con.setWindowTitle("请先配置socket参数信息!");
    con.exec();
    camauto = new CameraAuto();
    camset = new CameraSet();


    connect(camset,SIGNAL(close_signal()),
            this,SLOT(close_slot()));
    connect(camauto,SIGNAL(close_signal()),
            this,SLOT(close_slot()));
    connect(this,SIGNAL(initSet()),
            camset,SLOT(connectSocket()));
    connect(this,SIGNAL(initAuto()),
            camauto,SLOT(connectSocket()));

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
    emit initSet();
    camset->show();
}

void Client::close_slot()
{
    this->show();
}

void Client::on_btn_auto_clicked()
{
    this->hide();
    emit initAuto();
    camauto->show();
}
