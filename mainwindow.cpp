#include "mainwindow.h"
#include "GraphView.h"
#include "ExecutionEngine.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>

MainWindow::MainWindow()
{
    QWidget* central = new QWidget();
    setCentralWidget(central);

    QHBoxLayout* root = new QHBoxLayout(central);

    // ================= LEFT PANEL (OPERATORS) =================
    leftPanel = new QWidget();
    leftPanel->setFixedWidth(170);

    QVBoxLayout* leftLayout = new QVBoxLayout(leftPanel);

    createOperatorButtons(leftLayout);

    leftPanel->setStyleSheet(
        "QWidget{background:#0d0d0d;border-right:1px solid #222;}"
        "QPushButton{background:#141414;color:white;border-radius:10px;padding:6px;font-weight:bold;}"
        "QPushButton:hover{background:#1f1f1f;}"
        );

    // ================= CENTER GRAPH =================
    view = new GraphView();

    root->addWidget(leftPanel);
    root->addWidget(view,1);

    // ================= RIGHT PANEL =================
    rightPanel = new QWidget();
    rightPanel->setFixedWidth(180);

    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);

    rightPanel->setStyleSheet(
        "QWidget{background:#0d0d0d;border-left:1px solid #222;}"
        "QPushButton{background:#141414;color:white;border-radius:10px;padding:6px;font-weight:bold;}"
        "QPushButton:hover{background:#1f1f1f;}"
        );

    // ⭐ NODE SPAWN BUTTON HELPER
    auto addNodeBtn = [=](QString name)
    {
        QPushButton* b = new QPushButton(name);
        rightLayout->addWidget(b);

        connect(b,&QPushButton::clicked,[=]()
                {
                    view->spawnNode(name);
                });
    };

    addNodeBtn("Variable");
    addNodeBtn("Compare");
    addNodeBtn("If");
    addNodeBtn("Output");

    // ================= RUN BUTTON =================
    QPushButton* runBtn = new QPushButton("Run");
    rightLayout->addWidget(runBtn);

    connect(runBtn,&QPushButton::clicked,[=]()
            {
                engine.run(view);
            });

    // ================= CLEAR GRAPH BUTTON =================
    QPushButton* clearBtn = new QPushButton("Exit");
    rightLayout->addWidget(clearBtn);

    connect(clearBtn,&QPushButton::clicked,[=]()
            {
                view->clearGraph();
            });

    root->addWidget(rightPanel);
}


// ============================================================
// ⭐ LEFT PANEL OPERATORS
// ============================================================

void MainWindow::createOperatorButtons(QVBoxLayout* layout)
{
    auto addOp=[=](QString name)
    {
        QPushButton* b=new QPushButton(name);
        layout->addWidget(b);

        connect(b,&QPushButton::clicked,[=]()
                {
                    view->spawnNode(name);
                });
    };

    // -------- ARITHMETIC --------
    addOp("Add");
    addOp("Subtract");
    addOp("Multiply");
    addOp("Divide");

    // -------- LOGIC --------
    addOp("Logical AND");
    addOp("Logical OR");
    addOp("Logical NOT");
}
