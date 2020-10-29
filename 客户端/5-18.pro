#-------------------------------------------------
#
# Project created by QtCreator 2020-10-13T12:40:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 5-18-4
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    chat.cpp \
    myboard.cpp \
    mykeyboard.cpp \
    registerform.cpp \
    recv.cpp \
    send.cpp \
    emjoy.cpp

HEADERS  += \
    login.h \
    chat.h \
    myboard.h \
    mykeyboard.h \
    registerform.h \
    recv.h \
    send.h \
    emjoy.h

FORMS    += \
    login.ui \
    chat.ui \
    mykeyboard.ui \
    registerform.ui \
    recv.ui \
    send.ui \
    emjoy.ui

CONFIG += C++11
