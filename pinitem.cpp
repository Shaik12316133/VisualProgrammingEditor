#include "PinItem.h"
#include "GraphView.h"
#include "NodeItem.h"

#include <QGraphicsSceneMouseEvent>

PinItem::PinItem(NodeItem* owner, Type t)
    : QGraphicsEllipseItem(owner)
{
    node = owner;
    pinType = t;

    setRect(0,0,12,12);

    // ⭐ RESTORED COLOR SCHEME
    switch(pinType)
    {
    case Input:
        setBrush(QColor(40,40,40));
        break;

    case Output:
        setBrush(QColor(0,255,247)); // cyan
        break;

    case Yes:
        setBrush(QColor(0,255,120)); // green
        break;

    case No:
        setBrush(QColor(255,60,60)); // red
        break;
    }

    setAcceptedMouseButtons(Qt::LeftButton);
}


void PinItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!scene()) return;

    if(scene()->views().isEmpty()) return;

    GraphView* view =
        dynamic_cast<GraphView*>(scene()->views().first());

    if(view)
        view->beginWireDrag(this);

    event->accept();
}
