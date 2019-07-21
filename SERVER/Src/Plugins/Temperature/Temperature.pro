#-------------------------------------------------
#
# Project created by QtCreator 2019-01-22T01:44:38
#
#-------------------------------------------------

QT       += core sql network
QT       -= gui

TEMPLATE = lib
CONFIG += plugin

CONFIG += debug_and_release
CONFIG += build_all

INCLUDEPATH += ../../Interface/MysqlDB
INCLUDEPATH += ../../Interface/Temperature
INCLUDEPATH += ../../Include/Temperature


CONFIG(debug, debug|release){
    TARGET = StatusFiled
    DESTDIR = ../../../Build/Debug/Plugin/Temperature
} else {
    TARGET = StatusFile
    DESTDIR = ../../../Build/Release/Plugin/Temperature
}
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Temperature.cpp

HEADERS += \
    Temperature.h
DISTFILES += Temperature.json 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
