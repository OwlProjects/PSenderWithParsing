QT  += core network widgets
QT  -= gui

TEMPLATE = lib
DEFINES += PSPACKETSK_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    pspacketsk.cpp

HEADERS += \
    PSPacketsK_global.h \
    pspacketsk.h

INCLUDEPATH += D:\projects\Research_Ethernet\workspace\PacketSender-master\src

TARGET = KACAKH_Parser

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
