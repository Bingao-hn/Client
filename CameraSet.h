#ifndef CAMERASET_H
#define CAMERASET_H

#include <QDialog>

namespace Ui {
class CameraSet;
}

class CameraSet : public QDialog
{
    Q_OBJECT

public:
    explicit CameraSet(QWidget *parent = 0);
    ~CameraSet();

private slots:
    void on_set_clicked();

    void on_show_clicked();

    void slotReadyRead();

    void on_save_clicked();

private:
    Ui::CameraSet *ui;
};

#endif // CAMERASET_H
