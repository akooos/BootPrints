QT       += core
TEMPLATE = lib
CONFIG += staticlib

TARGET = BootPrintsCore

DEFINES += GIT_COMMIT_HASH='$(shell git describe --always)'

HEADERS += \
    config.h \
    common.h \
    mediaitem.h \
    interfaces/gallerymanager.h \
    interfaces/share.h \
    interfaces/plugin.h \
    exception.h \
    core.h \
    interfaces/configui.h \
    interfaces/internal.h \
    dispatcher.h

SOURCES += \
    mediaitem.cpp \
    core.cpp \
    dispatcher.cpp

INCLUDEPATH += \
    interfaces

BUILD_DIR = \
    ../../builds

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



