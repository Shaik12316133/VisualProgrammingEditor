#pragma once
#include <QObject>
#include <QString>
#include <QTimer>

#include "GraphView.h"
#include "NodeItem.h"
#include "VariableSystem.h"
#include "WireItem.h"

class ExecutionEngine : public QObject
{
    Q_OBJECT

public:
    ExecutionEngine(QObject* parent=nullptr);

    VariableSystem vars;

    void run(GraphView* view);

signals:
    void log(QString);
    void variableChanged(QString,double);

private:
    bool running = false;

    GraphView* activeView = nullptr;
    NodeItem* currentNode = nullptr;

    double flowValue = 0;
    bool condition = true;

    NodeItem* getNext(NodeItem* current,bool branchResult);
    NodeItem* findStartNode(GraphView* view);
};
