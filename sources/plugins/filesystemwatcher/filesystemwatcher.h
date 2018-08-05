#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QFileSystemWatcher>
#include <QThread>

#include <plugin.h>
#include <config.h>
#include <mediaitem.h>
#include <internal.h>

using namespace BootPrints::Interfaces;

class FileSystemWatcher : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid FILE "filesystemwatcher.json")
    Q_INTERFACES( BootPrints::Interfaces::Plugin )

    BEGIN_CONFIG("filesystemwatcher")
        CONFIG_PROPERTY(QStringList,watchList)
        CONFIG_PROPERTY(QStringList,fileExtensionWatchList)
        CONFIG_PROPERTY(QDateTime,lastCheckTimestamp)
    END_CONFIG

    QFileSystemWatcher watcher;
    BootPrints::Interfaces::Internal *core;
    QStringList extFilters;

private slots:
    void onDirectoryChanged(const QString& path);
public:
    FileSystemWatcher(QObject *parent = nullptr);
    void init(BootPrints::Interfaces::Internal *core) override;
    void dispose() override;


};

#endif // FILESYSTEMWATCHER_H
