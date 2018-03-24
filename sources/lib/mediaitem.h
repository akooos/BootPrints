#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <QUrl>
#include <QByteArray>

class MediaItem
{
    QUrl      fp;
    QByteArray sumhash;

    public:
      MediaItem(const QString &filepath, const QByteArray &hash);
      MediaItem(const QUrl &filepath, const QByteArray &hash);

     const QUrl & file() const;
     void setFile(const QString &value);

     const QByteArray & hash() const;
};

#endif // MEDIAITEM_H
