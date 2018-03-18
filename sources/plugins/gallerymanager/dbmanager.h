#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <gallerymanager.h>
#include <QtPlugin>

using namespace BootPrints::Interfaces;

class DBManager :public QObject, GalleryManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID GalleryManager_iid FILE "gallerymanager.json")
    Q_INTERFACES(BootPrints::Interfaces::Plugin  BootPrints::Interfaces::GalleryManager )
public:
    DBManager(QObject *parent = 0)
    {

    }
    void init( QHash<QString,BasePlugin*> deps ) override
    {

    }
    void dispose() override
    {

    }
    void read(unsigned int offset, unsigned int limit) override
    {

    }
};



#endif // DBMANAGER_H
