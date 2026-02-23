#include <QApplication>
#include "MainWindow.h"

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);

    a.setStyleSheet("QMainWindow{background:#111;color:#00ffaa;}");

    MainWindow w;
    w.resize(1500,850);
    w.show();

    return a.exec();
}
