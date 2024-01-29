#include "wangluo_shou.h"

#include <QPainterPath>

wangluo_shou::wangluo_shou(QWidget *parent)
    : QWidget{parent}
{

    ///图表初始化
    series=new QSplineSeries();

    axisX = new QValueAxis();
    axisY = new QValueAxis();


    chart=new QChart();
    chart->addSeries(series);
    ch_view=new QChartView(this);
    ch_view->setChart(chart);


    //添加坐标轴
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    //数据绑定坐标轴
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    //轴的显示区间
    axisX->setTickCount(6);//刻度个数
    axisX->setRange(0, 10);
    axisY->setRange(0, 20);

    //曲线抗锯齿
    ch_view->setRenderHint(QPainter::Antialiasing);

    chart->setBackgroundVisible(false);
    chart->axes(Qt::Horizontal).back()->setGridLineVisible(false); // 取消水平坐标轴延长线显示
    chart->axes(Qt::Vertical).back()->setGridLineVisible(false);   // 取消垂直坐标轴延长线显示
}

wangluo_shou::~wangluo_shou()
{
    ch_view->deleteLater();
    series->deleteLater();
    chart->deleteLater();
}

void wangluo_shou::paintEvent(QPaintEvent *event)
{
    my_paint.begin(this);
    my_paint.setPen(QColor(38, 38, 38));
    //设置网速的图像
    int height=this->height(),width=this->width();
    int jian_ge=width/3;//间隔

    ///画出半圆进度条
    QLinearGradient gradient(width/2-jian_ge-20, height/3-jian_ge-5, width/2+jian_ge,height/3+jian_ge);
    //画出第一层的灰色层
    gradient.setColorAt(0, QColor(85, 85, 85)); // 渐变起始颜色为白色
    gradient.setColorAt(1, QColor(85, 85, 85)); // 渐变结束颜色为蓝色

    my_paint.setBrush(gradient);
    my_paint.drawPie(width/2-jian_ge-40, height/3-jian_ge-35, width/2+jian_ge+40, height/3+jian_ge+35,-150*16, -240*16); // 添加半圆

    //画出一个渐变的中间层

    gradient.setColorAt(0, Qt::white); // 渐变起始颜色为白色
    gradient.setColorAt(1, Qt::blue); // 渐变结束颜色为蓝色
    // 将渐变设置为画刷
    my_paint.setBrush(gradient);
    my_paint.drawPie(width/2-jian_ge-40, height/3-jian_ge-35, width/2+jian_ge+40, height/3+jian_ge+35,-150*16, -jiaoDu*16); // 添加半圆


    //然后来一个黑色的半圆进行覆盖，就只剩下一个半圆进度条了
    gradient.setColorAt(0, QColor(38, 38, 38)); // 渐变起始颜色为白色
    gradient.setColorAt(1, QColor(38, 38, 38)); // 渐变结束颜色为蓝色
    my_paint.setBrush(gradient);
    my_paint.drawPie(width/2-jian_ge-20, height/3-jian_ge-10, width/2+jian_ge, height/3+jian_ge,-30*16, 240*16); // 添加半圆


    //
    my_paint.setPen(Qt::white);
    ///设置表盘数字/乘数为三角函数
    my_paint.drawText(QRect(width/2-jian_ge*0.8,height/3+jian_ge*0.5,height/3+50,width/2+50),"0");
    my_paint.drawText(QRect(width/2-jian_ge*1,height/3+jian_ge*0,height/3+50,width/2+50),"125");
    my_paint.drawText(QRect(width/2-jian_ge*0.8,height/3-jian_ge*0.5,height/3+50,width/2+50),"250");
    my_paint.drawText(QRect(width/2-jian_ge*0.5,height/3-jian_ge*0.8,height/3+50,width/2+50),"375");
    my_paint.drawText(QRect(width/2-jian_ge*0,height/3-jian_ge*1,height/3+50,width/2+50),"500");
    my_paint.drawText(QRect(width/2+jian_ge*0.5,height/3-jian_ge*0.8,height/3+50,width/2+50),"625");
    my_paint.drawText(QRect(width/2+jian_ge*0.8,height/3-jian_ge*0.5,height/3+50,width/2+50),"750");
    my_paint.drawText(QRect(width/2+jian_ge*1,height/3-jian_ge*0,height/3+50,width/2+50),"875");
    my_paint.drawText(QRect(width/2+jian_ge*0.8,height/3+jian_ge*0.5,height/3+50,width/2+50),"1000");

    ///设置表盘网速显示
    QPen pen(QColor(63, 158, 231));
    QFont font;
    font.setPointSize(16);
    my_paint.setPen(pen);
    my_paint.setFont(font);
    my_paint.drawText(QRect(width/2-12,height/3,height/3+50,width/2+50),QString::number(wangsu,'f',2));//显示网速
    my_paint.drawText(QRect(width/2-10,height/3+30,height/3+50,width/2+50),"MB/S");

    ///画指针
    gradient.setColorAt(0, Qt::blue); // 渐变起始颜色为蓝色
    gradient.setColorAt(1, Qt::blue); // 渐变结束颜色为蓝色


    my_paint.end();
    tuBiao();
    update();
}

void wangluo_shou::setWangsu(double x)
{

    wangsu=x;
    jiaoDu=240*x/1000;//角度的计算
    if(jiaoDu>240)
        jiaoDu=240;
    if(max<wangsu)
    {
        max=wangsu;
        axisY->setRange(0,max+10);
    }
    series->append(i,wangsu);
    //曲线滑动显示
    qreal addx = chart->plotArea().width() / 10;
    if(i > 10)
        chart->scroll(addx,0);
    i++;
}

void wangluo_shou::tuBiao()
{
    ch_view->resize(this->width(),this->height()/2);
    ch_view->move(0,this->height()/2);
}


