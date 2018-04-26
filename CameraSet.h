#ifndef CAMERASET_H
#define CAMERASET_H

#include <QDialog>
#include <QTcpSocket>
#include <QPixmap>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QDebug>
#include <QFileDialog>
#include <QScreen>

namespace Ui {
class CameraSet;
}

class CameraSet : public QDialog
{
    Q_OBJECT

public:
    explicit CameraSet(QWidget *parent = 0);
    ~CameraSet();
    QTcpSocket* set_socket;

private slots:
    void on_set_clicked();

    void on_show_clicked();

    void slotReadyRead();

    void on_save_clicked();

    void closeEvent(QCloseEvent *);//重写关闭事件

    void connectSocket();
signals:
    void close_signal();

private:
    Ui::CameraSet *ui;
};

#endif // CAMERASET_H
