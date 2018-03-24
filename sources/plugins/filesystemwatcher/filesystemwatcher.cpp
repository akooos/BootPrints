#include "filesystemwatcher.h"

FilesystemWatcher::FilesystemWatcher(QObject *parent):ShareReceived(parent)
{
}
void FilesystemWatcher::init( QHash<QString,BasePlugin*> deps )
{
    Q_UNUSED(deps)
    watcher.addPaths(config.watchList);

    bool checker = QObject::connect(
                             &watcher,
                             SIGNAL(directoryChanged(QString)),
                             this,
                             SLOT(onDirectoryChanged(QString))
                );

    Q_ASSERT(checker);

    Q_UNUSED(checker);
}
void FilesystemWatcher::dispose()
{
    bool checker = QObject::disconnect(
                             &watcher,
                             SIGNAL(directoryChanged(QString)),
                             this,
                             SLOT(onDirectoryChanged(QString))
                );

    Q_ASSERT(checker);

    Q_UNUSED(checker);

    watcher.removePaths(config.watchList);
}

void FilesystemWatcher::onDirectoryChanged(const QString &path)
{
    ///MediaItem mi(path,QByteArray());
    //emit newShareReceived(mi);
}
