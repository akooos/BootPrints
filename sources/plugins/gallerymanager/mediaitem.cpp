#include "mediaitem.h"


MediaItem::MediaItem(
   const QString &filepath,
   const QByteArray &sumhash
 ):
 fp(filepath),
 sumhash(sumhash)
{

}

const QFile & MediaItem::file() const
{
    return this->fp;
}

void MediaItem::setFile(const QString &value)
{
    this->fp.setFileName(value);
}

