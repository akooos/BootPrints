#ifndef SHARE_H
#define SHARE_H

#include "plugin.h"
#include "mediaitem.h"

namespace BootPrints::Interfaces
{
    class ShareReceived : public QObject, public Plugin
    {
        Q_OBJECT
    public:
        ShareReceived(QObject *parent = 0):QObject(parent)
        {

        }
      signals:
        virtual void newShareReceived(MediaItem file);
    };
}

#define ShareReceived_iid "org.Akooos.BootPrints.ShareReceived"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::ShareReceived, ShareReceived_iid)

#endif // SHARE_H
