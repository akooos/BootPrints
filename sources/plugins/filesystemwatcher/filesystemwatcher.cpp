
#include <QCryptographicHash>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QFile>
#include <QByteArray>
#include <QThread>

#include <interfaces/internal.h>
#include <mediaitem.h>

#include "filesystemwatcher.h"

FileSystemWatcher::FileSystemWatcher(QObject *parent):QObject(parent),core(nullptr),extFilters(QStringList() << "*.jpg" << "*.JPG" << "*.jpeg" << "*.png" << "*.PNG" << "*.bmp" << "*.mp4")
{

    bool checker = QObject::connect(
                             &watcher,
                             SIGNAL(directoryChanged(QString)),
                             this,
                             SLOT(onDirectoryChanged(QString))
                );

    Q_ASSERT(checker);

    Q_UNUSED(checker);
}
void FileSystemWatcher::init(BootPrints::Interfaces::Internal *core)
{
    this->core = core;

    if (!config.lastCheckTimestamp.exists() )
    {
        config.lastCheckTimestamp = QDateTime::fromSecsSinceEpoch(0);
    }
    extFilters = config.fileExtensionWatchList.value( extFilters ).value<QStringList>();

    DEBUG_MSG("Looking for files in:" << config.watchList.toString());

    watcher.addPaths(config.watchList);
}
void FileSystemWatcher::dispose()
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

void FileSystemWatcher::onDirectoryChanged(const QString &path)
{
    DEBUG_MSG("Directory content changed: " << path );

    if ( !core ){
        DEBUG_MSG("Nullptr of core interface.");
        return;
    }

    QDirIterator it(path, extFilters, QDir::Files, QDirIterator::Subdirectories);
    QDateTime lastCheckTimestamp = config.lastCheckTimestamp;
    while (it.hasNext())
    {
        QFileInfo fi(it.next());

        if (  fi.lastModified() >= lastCheckTimestamp )
        {
            core->addMediaItem(MediaItem(fi.absoluteFilePath(),QByteArray()));
        }
        else
        {
            DEBUG_MSG("Ignoring file, because last check time is greater that modification time" << fi.absoluteFilePath())
        }
    }

    config.lastCheckTimestamp = QDateTime::currentDateTime();
}
