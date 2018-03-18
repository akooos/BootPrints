TEMPLATE = lib
CONFIG += staticlib

TARGET = BootPrintsCore

#version.target = version.h
#version.depends = FORCE
#version.commands = git describe --always
#PRE_TARGETDEPS += version.h
#QMAKE_EXTRA_TARGETS += version

HEADERS += \
    config.h \
    common.h \
    interfaces/gallerymanager.h \
    interfaces/share.h \
    interfaces/plugin.h \
    version.h \
    exception.h \
    version.h \
    core.h

SOURCES += \
    core.cpp

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



