# -------------------------------------------------
# Project created by QtCreator 2009-11-16T15:02:19
# -------------------------------------------------
TEMPLATE = app

TARGET = qOthello

DESTDIR = ./
MOC_DIR = Build/Mocs
OBJECTS_DIR = Build/Objs

CONFIG += stl
SOURCES += main.cpp \
    game.cpp \
    buttons.cpp \
    Othcons/Scacchiera.cpp \
    Othcons/Giocatori.cpp \
    insertname.cpp \
    score_win.cpp \
    info.cpp \
    saveDialog.cpp
HEADERS += game.h \
    buttons.h \
    Othcons/Scacchiera.h \
    Othcons/Giocatori.h \
    insertname.h \
    score_win.h \
    info.h \
    saveDialog.h
OTHER_FILES += 
FORMS += saveDialog.ui

TRANSLATIONS += \
     qothello_en.ts

RESOURCES += \
    res.qrc
