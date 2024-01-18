#include "ellipse.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ellipse w;
    w.show();
    return a.exec();
}
