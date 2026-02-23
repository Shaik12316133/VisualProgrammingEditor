#pragma once

#include <QGraphicsObject>
#include <QVector>
#include <QComboBox>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>

class PinItem;
class WireItem;
class QGraphicsSimpleTextItem;

class NodeItem : public QGraphicsObject
{
public:
    NodeItem(QString type);

    QRectF boundingRect() const override;

    QString nodeType;
    QString varName;
    QString compareOp = "<";

    double numberValue = 0;

    PinItem *input,*output,*yesPin,*noPin;

    QVector<WireItem*> connectedWires;

    void setActive(bool a);

    //// ⭐ OUTPUT DISPLAY TEXT
    QGraphicsSimpleTextItem* outputLabel;
    void setOutputText(QString txt);

    //// ⭐ Unreal Compare UI
    QGraphicsTextItem* titleText = nullptr;
    QGraphicsProxyWidget* compareProxy = nullptr;
    QComboBox* compareBox = nullptr;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    QVariant itemChange(GraphicsItemChange,const QVariant&) override;
    void paint(QPainter*,const QStyleOptionGraphicsItem*,QWidget*) override;
};
