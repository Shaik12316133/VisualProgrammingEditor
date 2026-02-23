#include "Node.h"
#include <QBrush>

Node::Node(QString t)
{
    title = t;
    setRect(0,0,140,60);
    setBrush(QColor(40,40,40));
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);

    QGraphicsTextItem *text = new QGraphicsTextItem(title,this);
    text->setDefaultTextColor(Qt::green);
    text->setPos(10,10);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsRectItem::itemChange(change,value);
}
