#ifndef JUDGE_H
#define JUDGE_H

#include <QPainter>
#include <QVector>

class Judge
{
public:
    Judge();
    void PushBack_to_Polygons(QPolygon py);
    void ClearPolygons();
    bool JudgePoint(QPoint point);
//    void CreateFence();
//    void ClearFence();
//    QPolygon GetFence();

private:
    QVector<QPolygon> polygons;
//    QPolygon fencePolygon;
};

#endif // JUDGE_H
