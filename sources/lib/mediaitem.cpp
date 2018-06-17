#include "mediaitem.h"

MediaItem::MediaItem(const QString &filepath,
   const QByteArray &sumhash
 ):
 fp(filepath),
 sumhash(sumhash)
{

}


MediaItem::MediaItem(const QUrl &filepath,
   const QByteArray &sumhash
 ):
 fp(filepath),
 sumhash(sumhash)
{

}

const QUrl &MediaItem::file() const
{
    return this->fp;
}

void MediaItem::setFile(const QString &value)
{
    this->fp.setPath(value);
}

const QByteArray &MediaItem::hash() const
{
    return sumhash;
}

