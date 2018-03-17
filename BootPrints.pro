TEMPLATE = subdirs

SUBDIRS += \
    sources/lib \
    sources/gui \
    sources/plugins/gallerymanager \
    sources/plugins/trayicon


gui.depends = lib
gallerymanager.depends = lib
trayicon.depends = lib

OTHER_FILES += \
    README.md \
    TODO.txt

