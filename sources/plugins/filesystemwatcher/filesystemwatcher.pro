#-------------------------------------------------
#
# Project created by QtCreator 2018-03-24T11:37:07
#
#-------------------------------------------------

QT       += core gui

TARGET = FilesystemWatcher
TEMPLATE = lib

DEFINES += FILESYSTEMWATCHER_LIBRARY

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
        filesystemwatcher.cpp

HEADERS += \
        filesystemwatcher.h

INCLUDEPATH += ../../patterns \
               ../../lib \
               ../../lib/interfaces

CONFIG += plugin c++17
QMAKE_CXXFLAGS += -std=c++17

PLUGIN_DESC_FILES = $$lower($${TARGET}).json

OTHER_FILES = \
    $$lower($${TARGET}).json

BUILD_DIR=../../../builds

CONFIG(debug, debug|release) {
    DEFINES += DEBUG_MODE
    DESTDIR = $${BUILD_DIR}/debug
}
else:CONFIG(force_debug_info) {
    DEFINES += PROFILE_MODE
    DESTDIR = $${BUILD_DIR}/profile
}
else {
    DEFINES += RELEASE_MODE
    DESTDIR = $${BUILD_DIR}/release
}

CORE_DESTDIR = $${DESTDIR}_$${QMAKE_HOST.os}_$${QMAKE_HOST.arch}

DESTDIR = $${CORE_DESTDIR}/plugins

OTHERS_DEST_DIR = $$DESTDIR/$${TARGET}_parts
OBJECTS_DIR = $${OTHERS_DEST_DIR}/objs
MOC_DIR = $${OTHERS_DEST_DIR}/mocs
RCC_DIR = $${OTHERS_DEST_DIR}/rccs
UI_DIR = $${OTHERS_DEST_DIR}/uis

#add core dependecy
LIBS += -L$$CORE_DESTDIR -lBootPrintsCore
