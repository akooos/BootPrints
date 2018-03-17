TODO
------
    config for plugins, groupped by pluginname
    -
------
  uiplugin
   csak arra való hogy a beépített erőforrásokat,
   actionoket el lehessen érni pluginból

--------
 GUIFace interface vissza, csak másnéven...
 lenne egy  QWidget * widget() metódus, amiben
 saját grafikus felületet lehet csinálni

--------

VERSION.h does not generated.
-> fix
---------------

#define Plugin_iid "org.Akooos.BootPrints.Plugin"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::Plugin, Plugin_iid)
-> egy soros makróvá szebb legyen

---------------------

TrayIcon plugin
-> első gui plugin, megépítése segít kialakítani a keretrendszert

------------------

GalleryManager plugin
SQLite3 adatbázis épít a gépen található kép/videó fájlokról
műveletek:
    find, query, add, del, move, remove

--------------
Organizer plugin
függőségek: GalleryManger
műveletek:
    place(mediapath)
feladat:
   o- duplikációk megszűntetése a kiválaszott gallerymanager
   o- mappába rendezés, készítés év, hónap stb szerint például


------------
