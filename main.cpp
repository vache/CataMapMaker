#include "mapmaker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapMaker w;
    w.show();

    return a.exec();
}
