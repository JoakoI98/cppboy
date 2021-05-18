#include "interface/mainwindow.h"

#include <QApplication>

#include <SFML/Window.hpp>

#include "cpu/cpu.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    cppb::CPU cpu;
    QStringList initialState = cpu.getInfo(true) + cpu.getInfo(0x40, 0x48, false);
    w.refreshList(initialState);
    w.cpu = &cpu;

    w.show();
    return a.exec();
}
