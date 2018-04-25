#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private slots:
    void on_mCameraSet_triggered();

    void on_mConnect_triggered();


private:
    Ui::Client *ui;
};

#endif // CLIENT_H
