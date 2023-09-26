TEMPLATE = app

QT += widgets

FORMS += mainwindow.ui
SOURCES += main.cpp \
    filedialoghandler.cpp \
    qtablerefwidgetitem.cpp \
    savedatauiupdater.cpp \
    savemanager.cpp \
    stoopidqstringgenerator.cpp

MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build

DESTDIR = build

HEADERS += \
    filedialoghandler.h \
    qtablerefwidgetitem.h \
    savedatauiupdater.h \
    savemanager.h \
    stoopidqstringgenerator.h

unix:!macx: LIBS += -L$$PWD/libNepNep/ -lnepnep

INCLUDEPATH += $$PWD/libNepNep/include
DEPENDPATH += $$PWD/libNepNep/include

#unix:!macx: LIBS += -lssl

#unix:!macx: LIBS += -lcrypto
