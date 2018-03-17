#-------------------------------------------------
#
# Project created by QtCreator 2018-02-25T09:11:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BootPrints
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++17
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
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    uiplugin.h

INCLUDEPATH += \
    ../patterns \
    ../lib \
    ../lib/interfaces \
    ../../resources/uis

FORMS += \
    ../../resources/uis/mainwindow.ui

RESOURCES += \
    ../../resources/icons/icons.qrc

win {
    RC_ICONS = ../resources/icons/app_main_icon.ico
}

BUILD_DIR = ../../builds

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

DESTDIR = $${DESTDIR}_$${QMAKE_HOST.os}_$${QMAKE_HOST.arch}

OTHERS_DEST_DIR = $$DESTDIR/$${TARGET}_parts

OBJECTS_DIR = $${OTHERS_DEST_DIR}/objs
MOC_DIR = $${OTHERS_DEST_DIR}/mocs
RCC_DIR = $${OTHERS_DEST_DIR}/rccs
UI_DIR = $${OTHERS_DEST_DIR}/uis

