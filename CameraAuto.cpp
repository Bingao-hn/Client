#include "CameraAuto.h"
#include "ui_CameraAuto.h"

extern QTcpSocket* _socket;

CameraAuto::CameraAuto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraAuto)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(autoGet_slot()));

    connect(_socket, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));
}

CameraAuto::~CameraAuto()
{
    delete ui;
}

void CameraAuto::closeEvent(QCloseEvent *event)
{
    timer->stop();
    emit close_signal();
}

void  CameraAuto::slotReadyRead()
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
        qDebug() << "qt auto received";
    }
}
void CameraAuto::on_btn_start_clicked()
{
    timer->start(2000);//设置时间间隔
}

void CameraAuto::autoGet_slot()
{
    qDebug()<<"auto get picture . . . ";
//    QString strText = "get picture";
//    _socket->write(strText.toUtf8());
    int i=QDateTime::currentDateTime().toTime_t();
    QString fileName = "F:/bishe_data/"+QDateTime::fromTime_t(i).toString("yyyy-MM-dd-hh_mm_ss")+".png";
    QImage image("F:/logo.jpg");

    image.save(fileName);

}

void CameraAuto::on_btn_stop_clicked()
{
    timer->stop();
}
