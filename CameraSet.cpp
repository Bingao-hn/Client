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

    //更新UI
    connect(recvThread_set, SIGNAL(sendMessage(QString)),
               this, SLOT(receiveResult(QString)));

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
    //取巧
//    QString trick = "picture";
//    set_socket->write(trick.toUtf8());
//    set_socket->write(trick.toUtf8());
//    set_socket->write(trick.toUtf8());
//    set_socket->write(trick.toUtf8());
//    set_socket->write(trick.toUtf8());
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
    QString filename = QFileDialog::getOpenFileName(this,tr("请选择测试图片!"),"",tr("Images (*.png)")); //选择路径
//    QFileDialog::getOpenFileName()
    ui->test_pic->setText(filename);
//    qDebug()<<filename;
}

void CameraSet::on_start_test_clicked()
{

    testPic = ui->test_pic->text();
//    QString cmd = "result.py 1-8.png";
    QString cmd = "result.py " + testPic;
    emit sendCMD(cmd);
    recvThread_set->start();

    QMovie *movie = new QMovie(":\\image\\processing.gif");
    //QMovie *movie = new QMovie("D:\\QTclient\\client2\\onSaving.gif");
    ui->lab_status->setMovie(movie);
    movie->start();

    QPixmap pixmap(testPic);
    ui->lab_pic->setPixmap(pixmap);
}

void CameraSet::receiveResult(const QString &str)
{
    if(str.isEmpty())
    {
        QString info = "请检查服务器连接!";

        qDebug()<<"empty";
    }
    else{
      //  int i=QDateTime::currentDateTime().toTime_t();
      //  QString time = QDateTime::fromTime_t(i).toString("yyyy-MM-dd-hh:mm:ss ");
        QString send = testPic + "结果:" +str;
        ui->textEdit_recv->append(send);
        qDebug()<<send;
    }
//    qDebug()<<"changed";
    QPixmap pixmap(":\\image\\sleep.jpg");
    ui->lab_status->setPixmap(pixmap);
}

void CameraSet::on_btn_clear_clicked()
{
    ui->textEdit_recv->clear();
}


void CameraSet::on_btn_save_clicked()
{
    QString textFile = QFileDialog::getSaveFileName(this,tr("Save txt"),"",tr("text (*.txt)")); //选择路径
    //将文本框数据取出并按行排列
    QFile file(textFile);//文件命名
    if (!file.open(QFile::WriteOnly | QFile::Text))     //检测文件是否打开
    {
        QMessageBox::information(this, "提示", "导出失败，请重新导出!");
        return;
    }
    QTextStream out(&file);                 //分行写入文件
    out << ui->textEdit_recv->toPlainText();
}
