#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T17:38:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        Client.cpp \
    CameraSet.cpp \
    Connect.cpp

HEADERS  += Client.h \
    CameraSet.h \
    Connect.h

FORMS    += Client.ui \
    CameraSet.ui \
    Connect.ui
