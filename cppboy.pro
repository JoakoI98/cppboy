QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cartridge/cartridge.cpp \
    cpu/cpu.cpp \
    cpu/cpu_debug.cpp \
    main.cpp \
    interface/mainwindow.cpp \
    memory/memoryblock.cpp \
    memory/memorymanager.cpp \
    memory/memorysegment.cpp \
    memory/memorysegment_readonly.cpp \
    interface/qsfmlcanvas.cpp

HEADERS += \
    cartridge/ROM.h \
    cartridge/cartridge.h \
    cpu/cpu.h \
    cpu/cpu_debug.h \
    interface/mainwindow.h \
    memory/memoryblock.h \
    memory/memorymanager.h \
    memory/memorysegment.h \
    memory/memorysegment_readonly.h \
    interface/qsfmlcanvas.h

FORMS += \
    interface/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../../../../libs/SFML-2.5.1-MINGW/include
DEPENDPATH += $$PWD/../../../../libs/SFML-2.5.1-MINGW/include


CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../libs/SFML-2.5.1-MINGW/lib/ -lsfml-system -lsfml-graphics -lsfml-window
CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../libs/SFML-2.5.1-MINGW/lib/ -lsfml-system-d -lsfml-graphics-d -lsfml-window-d

