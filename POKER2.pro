#-------------------------------------------------
#
# Project created by QtCreator 2017-05-07T14:37:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = POKER2
TEMPLATE = app


SOURCES += main.cpp\
        login_window.cpp \
    register_window.cpp \
    user_window.cpp \
    game.cpp

HEADERS  += login_window.h \
    player.h \
    register_window.h \
    user_window.h \
    game.h

FORMS    += login_window.ui \
    register_window.ui \
    user_window.ui \
    game.ui

RESOURCES += \
    resources.qrc
