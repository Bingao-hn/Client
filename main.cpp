#include "Client.h"
#include <QApplication>
#include <QTcpSocket>

QString serverIp;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    QString title = "土壤湿度在线检测系统 ";
    w.setWindowTitle(QString::fromUtf8("土壤湿度在线检测系统客户端 "));
    w.show();
    return a.exec();
}
