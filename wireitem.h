#pragma once
#include <QGraphicsPathItem>

class PinItem;

class WireItem : public QGraphicsPathItem
{
public:
    WireItem(PinItem* s, PinItem* e);

    PinItem* start;
    PinItem* end;

    void updatePath(QPointF mousePos = QPointF());

    //// ⭐ UNREAL EXECUTION ANIMATION
    void advanceAnim();

protected:
    void paint(QPainter *p,
               const QStyleOptionGraphicsItem *,
               QWidget *) override;

private:
    qreal animOffset = 0;      //// moving pulse
};
