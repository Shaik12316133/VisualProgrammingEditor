#pragma once
#include <QGraphicsPathItem>

class PinItem;

class ConnectionItem : public QGraphicsPathItem
{
public:
    ConnectionItem(PinItem* a,PinItem* b);

    PinItem* start;
    PinItem* end;

    void updatePath();
};
