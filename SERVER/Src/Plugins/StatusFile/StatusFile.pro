#-------------------------------------------------
#
# Project created by QtCreator 2019-01-14T03:19:02
#
#-------------------------------------------------

QT       += core sql xml
QT       -= gui


TEMPLATE = lib
CONFIG += plugin

CONFIG += debug_and_release
CONFIG += build_all

INCLUDEPATH += ../../Interface/MysqlDB
INCLUDEPATH += ../../Interface/StatusFile
INCLUDEPATH += ../../Include/StatusFile

CONFIG(debug, debug|release){
    TARGET = StatusFiled
    DESTDIR = ../../../Build/Debug/Plugin/StatusFile
} else {
    TARGET = StatusFile
    DESTDIR = ../../../Build/Release/Plugin/StatusFile
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
    StatusFileplugin.cpp

HEADERS += \
    StatusFileplugin.h
DISTFILES += StatusFile.json 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
