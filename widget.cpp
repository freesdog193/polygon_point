#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QElapsedTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(1600, 1200);
    pix = QPixmap(560, 560);
    pix.fill(Qt::white);

    showPolygon = false;
    showPoint = false;
    showJudgePoint = false;
    showFence = false;
}

Widget::~Widget()
{
    delete ui;
}

/*******************绘图事件*********************/
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if(showPolygon)
    {
        QPainter pPoint(&pix);
        pPoint.setPen(QPen(Qt::blue, 3));
        QPolygon py;
        py = polygon;
        pPoint.drawPolygon(py);
        judger.PushBack_to_Polygons(polygon);
        polygon.clear();
        showPolygon = false;
    }
    if(showPoint)
    {
        QPainter pPolygon(&pix);
        pPolygon.setPen(QPen(Qt::red, 4));
        pPolygon.drawPoint(mousePosX, mousePosY);
        showPoint = false;
    }
    if(showJudgePoint)
    {
        QPainter pJPoint(&pix);
//        QElapsedTimer timer;
//        timer.start();
        if(judger.JudgePoint(QPoint(mousePosX, mousePosY)))
        {
            pJPoint.setPen(QColor(Qt::red));
            pJPoint.setBrush(QBrush(Qt::red));
        }
        else
        {
            pJPoint.setPen(QColor(Qt::darkGray));
            pJPoint.setBrush(QBrush(Qt::darkGray));
        }
//        qDebug() << "time:" << timer.elapsed() << "ms";

        pJPoint.drawEllipse(QPointF(mousePosX, mousePosY), 5, 5);
        showJudgePoint = false;
    }
    if(showFence)
    {
        QPainter pFence(&pix);
        pFence.setPen(QPen(Qt::blue, 3));
        pFence.drawPolygon(judger.GetFence());
        showFence = false;
    }
    painter.drawPixmap(20, 20, pix);
    painter.setPen(QPen(Qt::gray, 4));
    painter.drawLine(20, 20, 580, 20);
    painter.drawLine(20, 20, 20, 580);
    painter.setPen(QPen(Qt::gray, 2));
    for(int i = 20; i < 570; i += 20)
    {
        painter.drawLine(i + 20, 20, i + 20, 25);
        painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
        painter.drawText(i, 10, QString::number(i - 20));
        painter.drawLine(i + 20, 25, i + 20, 580);
    }
    painter.setPen(QPen(Qt::gray, 2));
    for(int i = 20; i < 570; i += 20)
    {
        painter.drawLine(20, i + 20, 25, i + 20);
        painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
        painter.drawText(1, i, QString::number(i - 20));
        painter.drawLine(25, i + 20, 580, i + 20);
    }
}

/*************************鼠标事件***************************/
void Widget::mousePressEvent(QMouseEvent *event)  //鼠标按下
{
    if(event->button() == Qt::LeftButton) //左键按下
    {
        mousePosX = event->x() - 20;
        mousePosY = event->y() - 20;
        polygon.push_back(QPoint(mousePosX, mousePosY));
        showPoint = true;
        this->update();
    }
    if(event->button() == Qt::RightButton) //右键按下
    {
        mousePosX = event->x() - 20;
        mousePosY = event->y() - 20;
        ui->pos_x->setText(QString("%1").arg(mousePosX));
        ui->pos_y->setText(QString("%1").arg(mousePosY));
        showJudgePoint = true;
        this->update();
    }
}

/******************信号槽函数*******************/
void Widget::on_showButton_clicked()
{
    showPolygon = true;
    this->update();
}

void Widget::on_clearButton_clicked()
{
    judger.ClearPolygons();
    judger.ClearFence();
    QPixmap clearPix = QPixmap(560, 560);
    clearPix.fill(Qt::white);
    pix = clearPix;
    this->update();
}

void Widget::on_drawPointButton_clicked()
{
    mousePosX = ui->pos_x->text().toDouble();
    mousePosY = ui->pos_y->text().toDouble();
    showJudgePoint = true;
    this->update();
}

void Widget::on_fenceButton_clicked()
{
    judger.CreateFence();
    showFence = true;
    this->update();
}

void Widget::drawAxis()
{

}

void Widget::on_quitButton_clicked()
{
    this->close();
}
