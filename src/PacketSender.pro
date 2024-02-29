#-------------------------------------------------
#
# Project created by QtCreator 2012-08-10T12:30:15
#
#-------------------------------------------------

QT  += core gui network widgets

TARGET = packetsender
TEMPLATE = app
DEFINES += GUI_BUILD

TRANSLATIONS += languages/packetsender_en.ts \
                languages/packetsender_es.ts \
                languages/packetsender_fr.ts \
                languages/packetsender_de.ts \
                languages/packetsender_hi.ts \
                languages/packetsender_it.ts

SOURCES += mainwindow.cpp \
    dialoglogparser.cpp \
    languagechooser.cpp \
    panel.cpp \
    sendpacketbutton.cpp \
    brucethepoodle.cpp \
    irisandmarigold.cpp \
    persistentconnection.cpp \
    about.cpp \
    subnetcalc.cpp \
    cloudui.cpp \
    multicastsetup.cpp \
    test_contextmenu.cpp \
    test_dll.cpp \
    test_qjson_parsing.cpp \
    udpflooding.cpp \
    packetlogmodel.cpp \
    postdatagen.cpp \
    panelgenerator.cpp \
    persistenthttp.cpp \
    wakeonlan.cpp

HEADERS  += mainwindow.h \
    InterfaceDLL.h \
    dialoglogparser.h \
    languagechooser.h \
    panel.h \
    sendpacketbutton.h \
    brucethepoodle.h \
    irisandmarigold.h \
    persistentconnection.h \
    about.h \
    subnetcalc.h \
    cloudui.h \
    multicastsetup.h \
    test_contextmenu.h \
    test_dll.h \
    test_qjson_parsing.h \
    udpflooding.h \
    packetlogmodel.h \
    postdatagen.h\
    panelgenerator.h \
    persistenthttp.h \
    wakeonlan.h

FORMS    += mainwindow.ui \
    brucethepoodle.ui \
    dialoglogparser.ui \
    irisandmarigold.ui \
    languagechooser.ui \
    persistentconnection.ui \
    settings.ui \
    about.ui \
    subnetcalc.ui \
    cloudui.ui \
        multicastsetup.ui \
    test_contextmenu.ui \
    test_dll.ui \
    test_qjson_parsing.ui \
    udpflooding.ui \
        persistenthttp.ui \
        postdatagen.ui \
    panelgenerator.ui \
    wakeonlan.ui

include(packetsender_main.pri)

INCLUDEPATH += ..\..\dll\dllClass\dllClass
DEPENDPATH += ..\..\dll\dllClass\dllClass

LIBS += debug\dllClass.dll

DISTFILES +=

