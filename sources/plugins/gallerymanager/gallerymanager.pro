TARGET = GalleryManager

TEMPLATE = lib

QT += core widgets sql

CONFIG += plugin c++17
QMAKE_CXXFLAGS += -std=c++17
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += mediadb.cpp

HEADERS += mediadb.h \
           dbmanager.h

INCLUDEPATH += ../../patterns \
               ../../lib \
               ../../lib/interfaces

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
