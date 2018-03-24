#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QFileSystemWatcher>

#include <config.h>
#include <share.h>

using namespace BootPrints::Interfaces;

namespace  {
    extern char const config_group_name[] = "filesystemwatcher";
}

class FilesystemWatcher :public ShareReceived
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ShareReceived_iid FILE "filesystemwatcher.json")
    Q_INTERFACES( BootPrints::Interfaces::ShareReceived)

    struct Config : BootPrints::Config<config_group_name> {
        CONFIG_PROPERTY(QStringList,watchList)
    } config;

    QFileSystemWatcher watcher;
private slots:
    void onDirectoryChanged(const QString &path);
public:
    FilesystemWatcher(QObject *parent = 0);
    void init( QHash<QString,BasePlugin*> deps ) override;
    void dispose() override;


};

#endif // FILESYSTEMWATCHER_H
