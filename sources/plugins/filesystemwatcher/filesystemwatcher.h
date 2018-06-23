#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QFileSystemWatcher>
#include <QThread>

#include <plugin.h>
#include <config.h>
#include <mediaitem.h>
#include <internal.h>

using namespace BootPrints::Interfaces;

namespace  {
    extern char const config_group_name[] = "filesystemwatcher";
    QStringList defFileExtensionWatchList =  QStringList() << "*.jpg" << "*.JPG" << "*.jpeg" << "*.png" << "*.PNG" << "*.bmp" << "*.mp4";
}

class Worker : public QObject
{
    Q_OBJECT


public:
    qint64 readBufferSize;
    QStringList fileExtensionWatchList;

    Worker(QObject *parent = 0):QObject(parent),
     readBufferSize(1024*1024*4),
     fileExtensionWatchList( defFileExtensionWatchList )
    {


    }

public slots:
    void onDirectoryChanged(const QString &path);
signals:
    void createdMediaItem(MediaItem mi);
};

class FileSystemWatcher : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid FILE "filesystemwatcher.json")
    Q_INTERFACES( BootPrints::Interfaces::Plugin )

    struct Config : BootPrints::Config<config_group_name> {
        CONFIG_PROPERTY(QStringList,watchList)
        CONFIG_PROPERTY(QStringList,fileExtensionWatchList)
        CONFIG_PROPERTY(QDateTime,lastCheckTimestamp)
    } config;

    QFileSystemWatcher watcher;
    BootPrints::Interfaces::Internal *core;
    QStringList extFilters;



private slots:
    void onDirectoryChanged(const QString& path);
public:
    FileSystemWatcher(QObject *parent = 0);
    void init(BootPrints::Interfaces::Internal *core) override;
    void dispose() override;


};

#endif // FILESYSTEMWATCHER_H
