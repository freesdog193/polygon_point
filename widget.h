#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include "judge.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void drawAxis();

private slots:
    void on_showButton_clicked();

    void on_clearButton_clicked();

    void on_drawPointButton_clicked();

    void on_fenceButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::Widget *ui;
    bool showPolygon;
    bool showPoint;
    bool showJudgePoint;
    bool showFence;
    double mousePosX;
    double mousePosY;
    QPixmap pix;
    QPolygon polygon;
    Judge judger;
};
#endif // WIDGET_H
