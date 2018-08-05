#ifndef MEDIADB_H
#define MEDIADB_H

#include <mediaitem.h>
#include <QFile>

class MediaDB
{
public:
    MediaDB();

    void add(const MediaItem &filepath);
    void del(const MediaItem &filepath);
    void update(const QByteArray &hash, const QFile &filepath);
    QList<MediaItem> get(unsigned int offset, unsigned int limit );


    void exists(const QFile &filepath) const;
    void exists(const QByteArray &hash) const;
    QByteArray hash(const QFile &filepath) const;
};

#endif // MEDIADB_H
