#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QProcess>
#include <QMessageBox>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    QProcess *running_process;
    QString arg_cmd;
    ~MyThread();
    void stop();

public:
    void run();

private:

signals:
    void sendMessage(const QString &);

public slots:
        void recvCMD(const QString &);
        void exit_slot();
        void init();
        void read_slot();
};


#endif // MYTHREAD_H
