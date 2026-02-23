#include "ConnectionItem.h"
#include "PinItem.h"
#include <QPainterPath>
#include <QPen>

ConnectionItem::ConnectionItem(PinItem* a,PinItem* b)
{
    start=a;
    end=b;
    setPen(QPen(QColor(0,255,170),3));
    updatePath();
}

void ConnectionItem::updatePath()
{
    if(!start||!end) return;

    QPointF p1=start->scenePos();
    QPointF p2=end->scenePos();

    QPainterPath path(p1);
    qreal dx=(p2.x()-p1.x())*0.5;

    path.cubicTo(p1.x()+dx,p1.y(),p2.x()-dx,p2.y(),p2.x(),p2.y());
    setPath(path);
}
