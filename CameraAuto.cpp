#include "CameraAuto.h"
#include "ui_CameraAuto.h"
extern QString serverIp;

CameraAuto::CameraAuto(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraAuto)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    auto_socket = new QTcpSocket();
    connect(timer, SIGNAL(timeout()), this, SLOT(autoGet_slot()));

    connect(auto_socket, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));
}

CameraAuto::~CameraAuto()
{
    delete ui;
}
void CameraAuto::connectSocket(){
    qDebug()<<serverIp;
    auto_socket->connectToHost(serverIp, 8080);
}
void CameraAuto::closeEvent(QCloseEvent *event)
{
    timer->stop();
    auto_socket->close();
    emit close_signal();
}

void  CameraAuto::slotReadyRead()
{
    // 接收数据，判断是否有数据，如果有，通过readAll函数获取所有数据
    while(auto_socket->bytesAvailable() > 0)
    {
        QByteArray array;
        while(auto_socket->waitForReadyRead(100)){
                   array.append((QByteArray)auto_socket->readAll());
               }
        QBuffer buffer(&array);
        buffer.open(QIODevice::ReadOnly);
        QImageReader reader(&buffer,"JPG");
        QImage img = reader.read();
        if(!img.isNull())
        {
            QPixmap pix = QPixmap::fromImage(img);
            ui->lab_pic->setPixmap(pix);

            //按时间保存图片
            int i=QDateTime::currentDateTime().toTime_t();
            QString fileName = "F:/bishe_data/"+QDateTime::fromTime_t(i).toString("yyyy-MM-dd-hh_mm_ss")+".png";
            img.save(fileName);
        }
        qDebug() << "qt auto received";
    }
}
void CameraAuto::on_btn_start_clicked()
{
    timer->start(10000);//设置时间间隔
}

void CameraAuto::autoGet_slot()
{
    qDebug()<<"auto get picture . . . ";
    //给服务器一个信号，让其发送图片
    QString strText = "get picture";
    auto_socket->write(strText.toUtf8());

}

void CameraAuto::on_btn_stop_clicked()
{
    timer->stop();
}
