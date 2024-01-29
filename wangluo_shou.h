#ifndef WANGLUO_SHOU_H
#define WANGLUO_SHOU_H

#include <QWidget>
#include<QPainter>
#include<QSplineSeries>
#include<QChartView>
#include <QValueAxis>
class wangluo_shou : public QWidget
{
    Q_OBJECT
public:
    explicit wangluo_shou(QWidget *parent = nullptr);
    ~wangluo_shou();
    void paintEvent(QPaintEvent *event);

    void setWangsu(double x);

    void tuBiao();
signals:

protected:
    QString name="下行";
    QPainter my_paint;
    double wangsu=0.00;
    double jiaoDu=0.00;
    QSplineSeries *series;//数据
    QChart *chart;  //图标
    QChartView *ch_view;//图标视图

    QValueAxis *axisX;
    QValueAxis *axisY;

    double max=0;
    int i=0;

};

#endif // WANGLUO_SHOU_H
