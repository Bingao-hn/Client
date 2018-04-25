#include "CameraAuto.h"
#include "ui_CameraAuto.h"

CameraAuto::CameraAuto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraAuto)
{
    ui->setupUi(this);
}

CameraAuto::~CameraAuto()
{
    delete ui;
}

void CameraAuto::on_pushButton_clicked()
{

}

void CameraAuto::closeEvent(QCloseEvent *event)
{
    emit close_signal();
}
