#include "GraphView.h"
#include "NodeItem.h"
#include "PinItem.h"
#include "WireItem.h"

#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QTimer>

GraphView::GraphView()
{
    setScene(new QGraphicsScene(this));
    setRenderHints(QPainter::Antialiasing |
                   QPainter::SmoothPixmapTransform);

    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorUnderMouse);

    QTimer* animTimer = new QTimer(this);

    connect(animTimer,&QTimer::timeout,[=]()
            {
                for(NodeItem* n : nodes)
                    for(WireItem* w : n->connectedWires)
                        if(w) w->advanceAnim();
            });

    animTimer->start(16);   //// 60 FPS animation

}

void GraphView::spawnNode(QString type)
{
    NodeItem* n=new NodeItem(type);

    QPointF p=mapToScene(viewport()->rect().center());
    n->setPos(p);

    scene()->addItem(n);
    nodes.append(n);
}

void GraphView::clearGraph()
{
    if(!scene()) return;

    //// ⭐ DELETE WIRES FIRST
    QList<QGraphicsItem*> allItems = scene()->items();

    for(QGraphicsItem* item : allItems)
    {
        WireItem* w = dynamic_cast<WireItem*>(item);
        if(w)
        {
            scene()->removeItem(w);
            delete w;
        }
    }

    //// ⭐ DELETE NODES
    for(NodeItem* n : nodes)
    {
        if(!n) continue;

        scene()->removeItem(n);
        delete n;
    }

    nodes.clear();
}

void GraphView::wheelEvent(QWheelEvent *e)
{
    double f=1.15;
    if(e->angleDelta().y()>0) scale(f,f);
    else scale(1.0/f,1.0/f);
}

void GraphView::beginWireDrag(PinItem* pin)
{
    dragStartPin=pin;
    activeWire=new WireItem(pin,nullptr);
    scene()->addItem(activeWire);
}

void GraphView::finishWireDrag(PinItem* pin)
{
    if(!activeWire) return;

    if(pin && pin!=dragStartPin &&
        pin->pinType!=dragStartPin->pinType)
    {
        activeWire->end=pin;
        activeWire->updatePath();

        dragStartPin->node->connectedWires.append(activeWire);
        pin->node->connectedWires.append(activeWire);
    }
    else
    {
        scene()->removeItem(activeWire);
        delete activeWire;
    }

    activeWire=nullptr;
    dragStartPin=nullptr;
}

void GraphView::mouseMoveEvent(QMouseEvent *e)
{
    if(activeWire)
        activeWire->updatePath(mapToScene(e->pos()));

    QGraphicsView::mouseMoveEvent(e);
}

void GraphView::mouseReleaseEvent(QMouseEvent *e)
{
    QList<QGraphicsItem*> itemsUnderMouse =
        scene()->items(mapToScene(e->pos()));

    PinItem* targetPin=nullptr;

    for(QGraphicsItem* it:itemsUnderMouse)
    {
        targetPin=dynamic_cast<PinItem*>(it);
        if(targetPin) break;
    }

    finishWireDrag(targetPin);

    QGraphicsView::mouseReleaseEvent(e);
}

