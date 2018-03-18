TEMPLATE = subdirs

SUBDIRS += \
    lib \
    gallerymanager \
    trayicon \
    gui

lib.subdir= sources/lib

gallerymanager.subdir = sources/plugins/gallerymanager
gallerymanager.depends = lib

trayicon.subdir =   sources/plugins/trayicon
trayicon.depends = lib

gui.subdir = sources/gui
gui.depends = lib

OTHER_FILES += \
    README.md \
    TODO.txt

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered
