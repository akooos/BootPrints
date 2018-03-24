TEMPLATE = subdirs

SUBDIRS += \
    lib \
    filesystemwatcher \
    gallerymanager \
    trayicon \
    gui \

lib.subdir= sources/lib

filesystemwatcher.subdir = sources/plugins/filesystemwatcher
filesystemwatcher.depends = lib

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
