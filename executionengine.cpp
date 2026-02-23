#include "ExecutionEngine.h"
#include "PinItem.h"
#include <QDebug>
#include <QTimer>
#include <QQueue>
#include <QPair>

ExecutionEngine::ExecutionEngine(QObject* parent)
    : QObject(parent)
{
}

void ExecutionEngine::run(GraphView* view)
{
    if(!view || view->nodes.isEmpty())
        return;

    NodeItem* start = findStartNode(view);
    if(!start) return;

    running = true;

    //// ⭐ EACH BRANCH HAS ITS OWN VALUE
    QQueue<QPair<NodeItem*,double>> queue;
    queue.enqueue(qMakePair(start, 0.0));

    while(!queue.isEmpty() && running)
    {
        auto pair = queue.dequeue();

        NodeItem* current = pair.first;
        double flowValue   = pair.second;

        if(!current) continue;

        current->setActive(true);

        QString t = current->nodeType;
        bool condition = true;

        // ================= VARIABLE =================
        if(t=="Variable")
        {
            flowValue = current->numberValue;
        }
        else if(t=="Add")
        {
            flowValue += current->numberValue;
        }
        else if(t=="Subtract")
        {
            flowValue -= current->numberValue;
        }
        else if(t=="Multiply")
        {
            flowValue *= current->numberValue;
        }
        else if(t=="Divide")
        {
            if(current->numberValue!=0)
                flowValue /= current->numberValue;
        }
        else if(t=="Logical AND")
        {
            flowValue = ((flowValue!=0)&&(current->numberValue!=0))?1:0;
        }
        else if(t=="Logical OR")
        {
            flowValue = ((flowValue!=0)||(current->numberValue!=0))?1:0;
        }
        else if(t=="Logical NOT")
        {
            flowValue = (flowValue==0)?1:0;
        }
        else if(t=="Compare")
        {
            double v=current->numberValue;

            if(current->compareOp=="<") condition = flowValue<v;
            else if(current->compareOp==">") condition = flowValue>v;
            else if(current->compareOp=="==") condition = flowValue==v;
            else if(current->compareOp=="!=") condition = flowValue!=v;
            else if(current->compareOp=="<=") condition = flowValue<=v;
            else if(current->compareOp==">=") condition = flowValue>=v;

            flowValue = condition ? 1 : 0;
        }
        else if(t=="Output")
        {
            QString result;

            if(flowValue==1 || flowValue==0)
                result = (flowValue==1) ? "True" : "False";
            else
                result = QString::number(flowValue);

            current->setOutputText(result);

            qDebug()<<"OUTPUT:"<<result;
        }

        current->setActive(false);

        //// ⭐ SEND VALUE TO ALL NEXT NODES
        for(WireItem* w : current->connectedWires)
        {
            if(!w || !w->start || !w->end) continue;
            if(w->start->node!=current) continue;

            if(current->nodeType=="If")
            {
                if(condition && w->start->pinType==PinItem::Yes)
                    queue.enqueue(qMakePair(w->end->node, flowValue));

                if(!condition && w->start->pinType==PinItem::No)
                    queue.enqueue(qMakePair(w->end->node, flowValue));
            }
            else
            {
                queue.enqueue(qMakePair(w->end->node, flowValue));
            }
        }
    }
}

//// =========================================================
/// ⭐ FIND START NODE
//// =========================================================
NodeItem* ExecutionEngine::findStartNode(GraphView* view)
{
    for(NodeItem* n : view->nodes)
        if(n->nodeType=="Variable")
            return n;

    return view->nodes.first();
}

//// =========================================================
/// ⭐ FLOW TRAVERSAL
//// =========================================================
NodeItem* ExecutionEngine::getNext(NodeItem* current,bool condition)
{
    for(WireItem* w : current->connectedWires)
    {
        if(!w || !w->start || !w->end) continue;
        if(w->start->node!=current) continue;

        if(current->nodeType=="If")
        {
            if(condition && w->start->pinType==PinItem::Yes)
                return w->end->node;

            if(!condition && w->start->pinType==PinItem::No)
                return w->end->node;
        }
        else
            return w->end->node;
    }
    return nullptr;
}
