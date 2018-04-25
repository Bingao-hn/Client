#include "Client.h"
#include <QApplication>
#include <QTcpSocket>

QTcpSocket* _socket;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();

    return a.exec();
}
