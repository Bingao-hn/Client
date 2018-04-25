#ifndef CAMERAAUTO_H
#define CAMERAAUTO_H

#include <QWidget>

namespace Ui {
class CameraAuto;
}

class CameraAuto : public QWidget
{
    Q_OBJECT

public:
    explicit CameraAuto(QWidget *parent = 0);
    ~CameraAuto();

private slots:
    void on_pushButton_clicked();

    void closeEvent(QCloseEvent *);//重写关闭事件
signals:
    void close_signal();
private:
    Ui::CameraAuto *ui;
};

#endif // CAMERAAUTO_H
