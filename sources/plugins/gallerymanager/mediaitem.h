#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <QFile>
#include <QByteArray>

class MediaItem
{
    QFile      fp;
    QByteArray sumhash;

    public:
      MediaItem(const QString &filepath, const QByteArray &hash);

     const QFile & file() const;
     void setFile(const QString &value);

     const QByteArray & hash() const;
};

#endif // MEDIAITEM_H
