#pragma once
#include <QMainWindow>
#include <QVBoxLayout>
#include "GraphView.h"
#include "ExecutionEngine.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    GraphView* view;
    ExecutionEngine engine;

    QWidget* leftPanel;
    QWidget* rightPanel;

    void createOperatorButtons(QVBoxLayout* layout);
};
