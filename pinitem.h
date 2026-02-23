#pragma once

#include <QGraphicsEllipseItem>

class NodeItem;
class WireItem;

class PinItem : public QGraphicsEllipseItem
{
public:

    enum Type
    {
        Input,
        Output,
        Yes,
        No
    };

    // ⭐ REQUIRED BY EXECUTION ENGINE
    NodeItem* node = nullptr;

    Type pinType = Input;

    WireItem* activeWire = nullptr;

    // ⭐ THIS CONSTRUCTOR MATCHES YOUR NODEITEM.CPP
    PinItem(NodeItem* owner, Type t);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};
