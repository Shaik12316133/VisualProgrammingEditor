#include "WireItem.h"
#include "PinItem.h"
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QtMath>

WireItem::WireItem(PinItem* s,PinItem* e)
{
    start=s;
    end=e;

    setZValue(-1); //// keep wires behind nodes
}

void WireItem::updatePath(QPointF mousePos)
{
    if(!start) return;

    QPointF p1=start->scenePos()+QPointF(6,6);
    QPointF p2=end?end->scenePos()+QPointF(6,6):mousePos;

    QPainterPath path(p1);

    qreal dx=(p2.x()-p1.x())*0.5;

    path.cubicTo(p1.x()+dx,p1.y(),
                 p2.x()-dx,p2.y(),
                 p2.x(),p2.y());

    setPath(path);
}

//// =======================================================
/// ⭐ UNREAL EXECUTION ENERGY PULSE
//// =======================================================
void WireItem::advanceAnim()
{
    animOffset += 0.04;
    update();
}

//// =======================================================
/// ⭐ CUSTOM PAINT (UNREAL STYLE)
//// =======================================================
void WireItem::paint(QPainter *p,
                     const QStyleOptionGraphicsItem *,
                     QWidget *)
{
    p->setRenderHint(QPainter::Antialiasing,true);

    QPainterPath path = this->path();

    //// BASE WIRE
    QPen base(QColor(0,120,160,180),2);
    base.setCapStyle(Qt::RoundCap);
    p->setPen(base);
    p->drawPath(path);

    //// ⭐ MOVING EXECUTION DOT
    qreal t = (qSin(animOffset*6)+1)/2.0;

    QPointF pt = path.pointAtPercent(t);

    QRadialGradient g(pt,8);
    g.setColorAt(0,QColor(0,255,255));
    g.setColorAt(1,QColor(0,255,255,0));

    p->setBrush(g);
    p->setPen(Qt::NoPen);
    p->drawEllipse(pt,8,8);
}
