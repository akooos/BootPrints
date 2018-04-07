#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QFileSystemWatcher>

#include <config.h>
#include <plugin.h>

using namespace BootPrints::Interfaces;

namespace  {
    extern char const config_group_name[] = "filesystemwatcher";
}

class FilesystemWatcher : public QObject, Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID Plugin_iid FILE "filesystemwatcher.json")
    Q_INTERFACES( BootPrints::Interfaces::Plugin )

    struct Config : BootPrints::Config<config_group_name> {
        CONFIG_PROPERTY(QStringList,watchList)
    } config;

    QFileSystemWatcher watcher;
    CorePtr core;
private slots:
    void onFileChanged(const QString &path);
public:
    FilesystemWatcher(QObject *parent = 0);
    void init(CorePtr core, QHash<QString,BasePlugin*> deps ) override;
    void dispose() override;


};

#endif // FILESYSTEMWATCHER_H
