#pragma once
#include <QGraphicsView>
#include <QVector>

class NodeItem;
class PinItem;
class WireItem;

class GraphView : public QGraphicsView
{
public:
    GraphView();

    QVector<NodeItem*> nodes;

    void spawnNode(QString type);
    void clearGraph();   //// ⭐ MUST BE PUBLIC

    WireItem* activeWire=nullptr;
    PinItem*  dragStartPin=nullptr;

    void beginWireDrag(PinItem*);
    void finishWireDrag(PinItem*);

protected:
    void wheelEvent(QWheelEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
};
