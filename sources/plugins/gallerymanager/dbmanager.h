#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <gallerymanager.h>
#include <mediaitemhandler.h>

#include <internal.h>
#include <common.h>
#include <mediaitem.h>
#include <QtPlugin>
#include <QUrl>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardPaths>
#include <config.h>

using namespace BootPrints::Interfaces;

class DBManager : public QObject, GalleryManager, MediaItemHandler
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID GalleryManager_iid FILE "gallerymanager.json")
    Q_INTERFACES(BootPrints::Interfaces::Plugin  BootPrints::Interfaces::GalleryManager )

    QSqlDatabase db;
public:
    BEGIN_CONFIG("gallerymanager")
        CONFIG_PROPERTY(QString,dbpath)
    END_CONFIG

    DBManager(QObject *parent = nullptr) : QObject(parent)
    {

    }
    void init( BootPrints::Interfaces::Internal *core) override
    {

        if (!config.dbpath.exists())
        {
            QString writeable_loc = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
            if ( writeable_loc.isEmpty()){
              DEBUG_MSG("Cannot write db to default path!");
              return;
            }else{

                if ( !QDir(writeable_loc).exists() )
                {
                    DEBUG_MSG("Database file location does not exist!" << writeable_loc)
                    return;
                }

                config.dbpath = writeable_loc;
            }
        }
      core->subscribeToShareProvider("FilesystemWatcher");
      db = QSqlDatabase::addDatabase("QSQLITE");
      QString db_name = config.dbpath + QDir::separator() + "gallery.db";
      DEBUG_MSG("Opening db:" << db_name)
      db.setDatabaseName( db_name );

         if (!db.open())
         {
            qDebug() << "Error: connection with database fail" << db.lastError();
            return;
         }
         else
         {
            qDebug() << "Database: connection ok";
         }
    }
    void dispose() override
    {

    }
    void read(unsigned int offset, unsigned int limit) override
    {

    }
    void newMediaItem(const MediaItem &mi) override
    {
        DEBUG_MSG("New share received" << mi.toString())
    }
};



#endif // DBMANAGER_H
