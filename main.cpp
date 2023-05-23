#include "autoservis.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    autoservis w;
    w.readUsers("users.txt");
    w.readCars("cars.txt");
    w.readSluzby("sluzby.txt");
    w.show();

    return a.exec();
}
