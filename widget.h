#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QThread>
#include<QLabel>
#include "tcp_thread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void timerEvent(QTimerEvent *event);

    void lan();
private slots:

signals:
    void read();
private:
    Ui::Widget *ui;
    QThread *thread1;
    tcp_thread *tcp;
    QLabel *ti_shi;
    QString chengun="background-color: rgba(0, 255, 0, 100); color: white;";
    QString shibai="background-color: rgba(255, 0, 0, 100); color: white;";
    int timer;
    int cishu=0;

};
#endif // WIDGET_H
