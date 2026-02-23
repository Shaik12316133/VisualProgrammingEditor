#pragma once
#include <QGraphicsLineItem>

class Node;

class Connection : public QGraphicsLineItem
{
public:
    Connection(Node* a, Node* b);

    Node* startNode;
    Node* endNode;

    void updatePosition();
};
