TEMPLATE = app

QT += widgets

FORMS += mainwindow.ui
SOURCES += main.cpp \
    filedialoghandler.cpp \
    savemanager.cpp

MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build

DESTDIR = build

HEADERS += \
    filedialoghandler.h \
    savemanager.h

unix:!macx: LIBS += -L$$PWD/libNepNep/ -lnepnep

INCLUDEPATH += $$PWD/libNepNep/include
DEPENDPATH += $$PWD/libNepNep/include
