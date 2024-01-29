#include "tcp_thread.h"

#include <QThread>

tcp_thread::tcp_thread(QObject *parent)
    : QObject{parent}
{
    qDebug() << "当前线程对象的地址: " << QThread::currentThread();
}

void tcp_thread::chuan_jian()
{
    qDebug() << "当前线程对象的地址: " << QThread::currentThread();;
    if(zt)
    {
        my_tcp=new QTcpSocket(this);
        my_tcp->connectToHost("192.168.0.107",10222);
        qDebug()<<my_tcp->thread();
        connect(my_tcp,&QTcpSocket::readyRead,this,[=](){

            //数据发送给主线程窗口
            if(cishu<=20)
            {
                double a=my_tcp->readAll().toDouble()/(1024*1024);
                qDebug()<<a;
                emit shangchuan_wangshu(a);
                cishu++;
            }
            else if(cishu==21)
            {
                emit xiazai();
                cishu++;
            }
            else
            {
                Date_sudu+=my_tcp->readAll().size();
            }
        });
        connect(my_tcp,&QTcpSocket::connected,this,[=](){
            zt=false;
            emit status(zt);
        });
        connect(my_tcp,&QTcpSocket::disconnected,this,[=](){
            zt=true;
            my_tcp->deleteLater();
            qDebug()<<"原来的tcp已经释放";
        });
        connect(my_tcp,&QTcpSocket::errorOccurred,this,[=](){
            zt=true;
            emit status(zt);
        });
    }
    fa();
}

void tcp_thread::fa()
{

    QElapsedTimer timer;
    timer.start();
    qDebug() << "开始运行 myFunction()...";
    while (timer.elapsed() < 5000) // 10秒 = 10000毫秒
    {
        QByteArray  a(1024,'a');
        my_tcp->write(a);

    }
    qDebug() << "myFunction() 运行结束";
}

void tcp_thread::xiazai_wangshu()
{
    emit Download(Date_sudu/(1024*1024));
    qDebug()<<Date_sudu;
    Date_sudu=0;
}


