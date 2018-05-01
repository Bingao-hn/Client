#include "CameraSet.h"
#include "ui_CameraSet.h"


extern QString serverIp;

CameraSet::CameraSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraSet)
{
    set_socket = new QTcpSocket();

    recvThread_set = new MyThread();

    connect(set_socket, SIGNAL(readyRead()),this, SLOT(slotReadyRead()));
    ui->setupUi(this);

    connect(this, SIGNAL(init_signal()), recvThread_set, SLOT(init()));
    emit init_signal();

    //获取输入命令，传送给子线程
    connect(this, SIGNAL(sendCMD(QString)),
               recvThread_set, SLOT(recvCMD(QString)));
}

CameraSet::~CameraSet()
{
    delete ui;
}



void CameraSet::on_show_clicked()
{
    //给服务器一个信号，让其发送图片
    QString strText = "get picture";
    set_socket->write(strText.toUtf8());
}

void CameraSet::connectSocket(){
    qDebug()<<serverIp;
    set_socket->connectToHost(serverIp, 8080);
}
void  CameraSet::slotReadyRead()
{
    // 接收数据，判断是否有数据，如果有，通过readAll函数获取所有数据
    while(set_socket->bytesAvailable() > 0)
    {
        QByteArray array;
        while(set_socket->waitForReadyRead(100)){
                   array.append((QByteArray)set_socket->readAll());
               }
        QBuffer buffer(&array);
        buffer.open(QIODevice::ReadOnly);
        QImageReader reader(&buffer,"JPG");
        img = reader.read();
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
    //QScreen *screen = QGuiApplication::primaryScreen();
    //screen->grabWindow(ui->lab_pic->winId()).save(filename1);
    qDebug()<<"set save path:"<<filename1;
    //保存图片
    img.save(filename1);
}

void CameraSet::closeEvent(QCloseEvent *event)
{
    emit close_signal();
    set_socket->close();
}

void CameraSet::on_select_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("请选择测试图片!"),"",tr("Images (*.png *.bmp *.jpg)")); //选择路径
//    QFileDialog::getOpenFileName()
    ui->test_pic->setText(filename);
//    qDebug()<<filename;
}

void CameraSet::on_start_test_clicked()
{

    QString cmd = "result.py 0 8.png";
    emit sendCMD(cmd);
    recvThread_set->start();
}
