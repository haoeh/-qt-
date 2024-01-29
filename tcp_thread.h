#ifndef TCP_THREAD_H
#define TCP_THREAD_H

#include <QObject>
#include<QTcpSocket>
class tcp_thread : public QObject
{
    Q_OBJECT
public:
    explicit tcp_thread(QObject *parent = nullptr);
    void chuan_jian();//创建QTcp
    void fa();//发送数据
    void xiazai_wangshu();

signals:
    void shangchuan_wangshu(double x);
    void Download(double x);
    void xiazai();

    void status(bool x);
private:
    double Date_sudu=0;
    QTcpSocket *my_tcp;
    bool zt=true;
    int cishu=0;
};

#endif // TCP_THREAD_H
