#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow w;
    BrushDialog b;
    w.setWindowTitle("Doodle Draw");
    w.show();
    return a.exec();
}
