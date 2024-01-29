#include "widget.h"
#include "ui_widget.h"
#include "wangluo_fa.h"

#include <QTimer>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    thread1=new QThread;//创建线程
    tcp=new tcp_thread;
    tcp->moveToThread(thread1);//将tcp类加入到子线程内
    thread1->start();//启动线程

    qDebug() << "当前线程对象的地址: " << QThread::currentThread();;

    connect(ui->pushButton,&QPushButton::clicked,tcp,&tcp_thread::chuan_jian);

        //点击开始然后连接服务器，根据服务器是否连接成功来显示提示栏
    connect(tcp,&tcp_thread::status,this,[=](bool x){
        if(!x)
        {
            ti_shi->setStyleSheet(chengun);
            ti_shi->setText("服务器连接成功");

        }
        else
        {
            ti_shi->setStyleSheet(shibai);
            ti_shi->setText("服务器连接失败，请检查网络情况");
        }
        ti_shi->setAlignment(Qt::AlignCenter);

        ti_shi->show();
        QTimer::singleShot(1000,[=](){
            ti_shi->setVisible(false);
        });

    });

    connect(tcp,&tcp_thread::shangchuan_wangshu,this,[=](double x){
        qDebug()<<x<<"MB/S";
        ui->widget_3->setWangsu(x);
    });

    connect(tcp,&tcp_thread::xiazai,this,[=](){
        qDebug()<<"接收下载数据";
        timer=startTimer(1000);
    });
    connect(this,&Widget::read,tcp,&tcp_thread::xiazai_wangshu);

    connect(tcp,&tcp_thread::Download,this,[=](double x){
        qDebug()<<x<<"MB/S";
        ui->widget_2->setWangsu(x);
    });
    //提示框的显示
    lan();

}

Widget::~Widget()
{
    thread1->deleteLater();
    delete ui;
}

void Widget::lan()
{
    //服务器连接状态提示栏
    ti_shi=new QLabel(this);
    ti_shi->setStyleSheet(chengun);
    ti_shi->setFixedSize(400, 30);
    ti_shi->move(this->width()/2-200,5);
    ti_shi->setVisible(false);

}

void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==1)
    {
        emit read();
        cishu++;
        if(cishu>30)
        {
            killTimer(event->timerId()); // 停止定时器
        }
    }
}






