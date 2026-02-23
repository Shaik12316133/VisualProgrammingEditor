#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include "Node.h"
#include "Connection.h"

class Canvas : public QGraphicsView
{
    Q_OBJECT
public:
    Canvas(QWidget* parent=nullptr);

    QGraphicsScene* scene;
    QVector<Node*> nodes;
    QVector<Connection*> connections;

    Node* createNode(QString name);
    void connectNodes(Node* a, Node* b);

    void saveToFile(QString path);
    void loadFromFile(QString path);

signals:
    void log(QString text);
};
