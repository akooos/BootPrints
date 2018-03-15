#ifndef MEDIADB_H
#define MEDIADB_H

#include <mediaitem.h>

class MediaDB
{
public:
    MediaDB();

    void add(const QFile &filepath);
    void del(const QFile &filepath);
    void set(const QByteArray &hash, const QFile &filepath);
    QList<MediaItem> get(unsigned int offset, unsigned int limit );


    void exists(const QFile &filepath) const;
    void exists(const QByteArray &hash) const;
    QByteArray hash(const QFile &filepath) const;
};

#endif // MEDIADB_H
