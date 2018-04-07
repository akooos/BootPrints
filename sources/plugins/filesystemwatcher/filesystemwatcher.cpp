#include "filesystemwatcher.h"

#include <interfaces/internal.h>

FilesystemWatcher::FilesystemWatcher(QObject *parent):QObject(parent)
{
}
void FilesystemWatcher::init(CorePtr core, QHash<QString,BasePlugin*> deps )
{
    this->core = core;
    Q_UNUSED(deps)
    watcher.addPaths(config.watchList);

    bool checker = QObject::connect(
                             &watcher,
                             SIGNAL(fileChanged(QString)),
                             this,
                             SLOT(onFileChanged(QString))
                );

    Q_ASSERT(checker);

    Q_UNUSED(checker);
}
void FilesystemWatcher::dispose()
{
    bool checker = QObject::disconnect(
                             &watcher,
                             SIGNAL(fileChanged(QString)),
                             this,
                             SLOT(onFileChanged(QString))
                );

    Q_ASSERT(checker);

    Q_UNUSED(checker);

    watcher.removePaths(config.watchList);
}

void FilesystemWatcher::onFileChanged(const QString &path)
{
    MediaItem mi(path,QByteArray());
    core->addNewMediaItem(mi);
}
