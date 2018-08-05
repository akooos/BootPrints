#ifndef MEDIAITEM_H
#define MEDIAITEM_H


#include <QCryptographicHash>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QFile>
#include <QByteArray>
#include <QUrl>
#include <QByteArray>

#include "common.h"

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

     const QString toString() const
     {
        return fp.toString() + "|" +  sumhash;
     }

     static MediaItem create(const QFileInfo &fi, const size_t max_read_buffer_size = 1024*1024*4)
     {
         QFile file(fi.absoluteFilePath());
         QCryptographicHash hashFunction(QCryptographicHash::Md5);
         qint64 return_code = -1;

         std::vector<char*> buffer { max_read_buffer_size , nullptr };

         if (!file.open(QIODevice::ReadOnly))
         {
             DEBUG_MSG("Could not open file:" << fi.absoluteFilePath());
             BootPrints::Exception::fail(BootPrints::ExceptionCodes::UnknownError, {"Could not open file:" + fi.absoluteFilePath()});
         }

         do
         {
             return_code = file.read( *buffer.data(), static_cast<qint64> ( max_read_buffer_size) );

             if ( return_code > 0 )
             {
                 DEBUG_MSG(return_code << "bytes were read from file:" << fi.absoluteFilePath())
                 hashFunction.addData( *buffer.data(), static_cast<int> (return_code) );
             } else
                 if ( return_code < 0 ) {
                     //error reading file: report error and quit
                     DEBUG_MSG("Failed to read from file:" << fi.absoluteFilePath() << "Read return code:" << return_code)
                 } else
                 {
                     QByteArray hash = hashFunction.result();
                     //nothing to read more, prepare hash
                     if ( !hash.isEmpty() )
                     {
                         DEBUG_MSG("Hash calculation finished for file:" << fi.absoluteFilePath() << "result:" << hash.toHex())
                         return MediaItem(fi.absoluteFilePath(),hash);
                     } else
                     {
                         DEBUG_MSG("Hash was empty, not emitting signal for other thread; file:" << fi.absoluteFilePath())
                     }
                     file.close();
                 }

         } while( return_code > 0 );

         return MediaItem(fi.absoluteFilePath(),hashFunction.result());
     }
};

#endif // MEDIAITEM_H
