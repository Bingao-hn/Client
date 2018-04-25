#include "CameraSet.h"
#include "ui_CameraSet.h"
#include <QTcpSocket>
#include <QPixmap>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QDebug>
#include <QFileDialog>
#include <QScreen>

extern QTcpSocket* _socket;

CameraSet::CameraSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraSet)
{
    connect(_socket, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));
    ui->setupUi(this);
}

CameraSet::~CameraSet()
{
    delete ui;
}

void CameraSet::on_set_clicked()
{
    //给服务器发送相机设置命令，由1开头，由“.”进行分割
    QString strText = "1." + ui->Ed_bright->text()+ "."  + ui->Ed_contrast->text() + "."  +ui->cB_iso->currentText();
    //qDebug()<<strText;
    _socket->write(strText.toUtf8());
}

void CameraSet::on_show_clicked()
{
    //给服务器一个信号，让其发送图片
    QString strText = "get picture";
    _socket->write(strText.toUtf8());
}

void  CameraSet::slotReadyRead()
{
    // 接收数据，判断是否有数据，如果有，通过readAll函数获取所有数据
    while(_socket->bytesAvailable() > 0)
    {
        QByteArray array;
        while(_socket->waitForReadyRead(100)){
                   array.append((QByteArray)_socket->readAll());
               }
        QBuffer buffer(&array);
        buffer.open(QIODevice::ReadOnly);
        QImageReader reader(&buffer,"JPG");
        QImage img = reader.read();
        if(!img.isNull())
        {
            QPixmap pix = QPixmap::fromImage(img);
            ui->lab_pic->setPixmap(pix);
        }
        qDebug() << "qt received";
    }
}

void CameraSet::on_save_clicked()
{
    QString filename1 = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
    QScreen *screen = QGuiApplication::primaryScreen();
    screen->grabWindow(ui->lab_pic->winId()).save(filename1);
}

void CameraSet::closeEvent(QCloseEvent *event)
{
    emit close_signal();
}
