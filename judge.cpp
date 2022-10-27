#include "judge.h"

Judge::Judge()
{

}

void Judge::PushBack_to_Polygons(QPolygon py)
{
    polygons.push_back(py);
}

void Judge::ClearPolygons()
{
    polygons.clear();
}

bool Judge::JudgePoint(QPoint point)
{
    if(fencePolygon.containsPoint(point, Qt::WindingFill))
        return true;
    for(auto iter = polygons.begin(); iter != polygons.end(); ++iter)
    {
        QPolygon py = *iter;
        if(py.containsPoint(point, Qt::WindingFill))
            return true;
    }

    return false;
}

void Judge::CreateFence()
{
    for(auto iter = polygons.begin(); iter != polygons.end(); ++iter)
    {
        QPolygon py = *iter;
        double x = 0;
        double y = 0;
        for(auto it = py.begin(); it != py.end(); ++it)
        {
            QPoint point = *it;
            x += point.x();
            y += point.y();
        }
        x /= py.size();
        y /= py.size();

        fencePolygon.push_back(QPoint(x, y));
    }
}

void Judge::ClearFence()
{
    fencePolygon.clear();
}

QPolygon Judge::GetFence()
{
    return fencePolygon;
}
