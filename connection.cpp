#include "Connection.h"
#include "Node.h"
#include <QPen>

Connection::Connection(Node* a, Node* b)
{
    startNode = a;
    endNode = b;
    setPen(QPen(Qt::green,2));
    updatePosition();
}

void Connection::updatePosition()
{
    if(!startNode || !endNode) return;

    QPointF p1 = startNode->scenePos() + QPointF(70,30);
    QPointF p2 = endNode->scenePos() + QPointF(70,30);
    setLine(QLineF(p1,p2));
}
