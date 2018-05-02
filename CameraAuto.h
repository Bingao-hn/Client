#ifndef CAMERAAUTO_H
#define CAMERAAUTO_H
#include "mythread.h"
#include <QWidget>
#include <QTcpSocket>
#include <QPixmap>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QDebug>
#include <QFileDialog>
#include <QScreen>
#include <QTimer>
#include <QDateTime>
#include <QMovie>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class CameraAuto;
}

class CameraAuto : public QWidget
{
    Q_OBJECT

public:
    explicit CameraAuto(QWidget *parent = 0);
    QTimer *timer;
    QTcpSocket* auto_socket;
    MyThread *recvThread_auto;
    ~CameraAuto();

private slots:
    void closeEvent(QCloseEvent *);//重写关闭事件

    void slotReadyRead();
    void on_btn_start_clicked();
    void autoGet_slot();
    void on_btn_stop_clicked();

    void connectSocket();

    void receiveResult(const QString &);//接收python脚本返回结果


    void on_btn_save_clicked();

signals:
    void close_signal();
    void init_signal();//初始化mythread线程
    void sendCMD(const QString &);
private:
    Ui::CameraAuto *ui;
};

#endif // CAMERAAUTO_H
