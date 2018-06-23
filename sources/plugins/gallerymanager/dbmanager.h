#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <gallerymanager.h>
#include <share.h>

#include <internal.h>
#include <common.h>

#include <QtPlugin>
#include <QUrl>
using namespace BootPrints::Interfaces;

class DBManager : public QObject, GalleryManager, Share
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID GalleryManager_iid FILE "gallerymanager.json")
    Q_INTERFACES(BootPrints::Interfaces::Plugin  BootPrints::Interfaces::GalleryManager )
public:
    DBManager(QObject *parent = 0) : QObject(parent)
    {

    }
    void init( BootPrints::Interfaces::Internal *core) override
    {
      core->subscribeToShareProvider("FilesystemWatcher");
    }
    void dispose() override
    {

    }
    void read(unsigned int offset, unsigned int limit) override
    {

    }
    void newShareReceived(const QUrl &url) override
    {
        DEBUG_MSG("New share received" << url.toString())
    }
};



#endif // DBMANAGER_H
