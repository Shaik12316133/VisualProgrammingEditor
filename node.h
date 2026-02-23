#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class Node : public QGraphicsRectItem
{
public:
    Node(QString title);

    QString title;
    int value = 0;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
};
