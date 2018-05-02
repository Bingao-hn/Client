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
    recvThread_auto = new MyThread();

    connect(timer, SIGNAL(timeout()), this, SLOT(autoGet_slot()));

    connect(auto_socket, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));

    connect(this, SIGNAL(init_signal()), recvThread_auto, SLOT(init()));
    emit init_signal();

    //更新UI
    connect(recvThread_auto, SIGNAL(sendMessage(QString)),
               this, SLOT(receiveResult(QString)));

    //获取输入命令，传送给子线程
    connect(this, SIGNAL(sendCMD(QString)),
               recvThread_auto, SLOT(recvCMD(QString)));
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

            //保存后马上开始测试该图
            QString cmd = "result.py 1-9.png";
            emit sendCMD(cmd);
            recvThread_auto->start();
        }
        qDebug() << "qt auto received";
    }
}
void CameraAuto::on_btn_start_clicked()
{
    timer->start(15000);//设置时间间隔

    QMovie *movie = new QMovie(":\\image\\processing.gif");
    //QMovie *movie = new QMovie("D:\\QTclient\\client2\\onSaving.gif");
    ui->lab_status->setMovie(movie);
    movie->start();
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

    QPixmap pixmap(":\\image\\sleep.jpg");
    ui->lab_status->setPixmap(pixmap);
}

void CameraAuto::receiveResult(const QString &str)
{
    if(str.isEmpty())
    {
        QString info = "请检查服务器连接!";
        ui->textEdit_recv->append(info);
        qDebug()<<"empty";
    }
    else{
        int i=QDateTime::currentDateTime().toTime_t();
        QString time = QDateTime::fromTime_t(i).toString("yyyy-MM-dd-hh:mm:ss ");
        QString send = time + "结果:" +str;
        ui->textEdit_recv->append(send);
    }
    qDebug()<<"changed";
}

void CameraAuto::on_pushButton_clicked()
{
    int i=QDateTime::currentDateTime().toTime_t();
    QString str = "123";
    QString time = QDateTime::fromTime_t(i).toString("yyyy-MM-dd-hh:mm:ss");
    QString send = time + "结果:" +str;
    ui->textEdit_recv->append(send);
}
