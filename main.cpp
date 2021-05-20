#include "interface/mainwindow.h"

#include <QApplication>

#include <SFML/Window.hpp>

#include "cpu/cpu.h"
#include "cpu/cpu_debug.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    cppb::CPU cpu;
    cppb::cpu_debug debug(cpu);
    QStringList initialState = debug.getInfo(true, true) + debug.getInfo(0x40, 0x48, false);
    w.refreshList(initialState);
    w.cpu = &cpu;
    w.debug = &debug;

    w.show();
    return a.exec();
}
