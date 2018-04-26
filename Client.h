#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "CameraSet.h"
#include "CameraAuto.h"
namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    CameraSet *camset;
    CameraAuto *camauto;
    ~Client();

private slots:
    void on_mCameraSet_triggered();

    void on_mConnect_triggered();

    void close_slot();

    void on_btn_manual_clicked();

    void on_btn_auto_clicked();
signals:
    void initSet();
    void initAuto();
private:
    Ui::Client *ui;
};

#endif // CLIENT_H
