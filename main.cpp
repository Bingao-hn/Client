#include "Client.h"
#include <QApplication>
#include <QTcpSocket>

QString serverIp;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();
    return a.exec();
}
