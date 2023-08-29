#include "inio_desktop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    inio_desktop w;
    w.show();
    return a.exec();
}
