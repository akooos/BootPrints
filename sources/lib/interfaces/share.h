#ifndef SHARE_H
#define SHARE_H

#include "plugin.h"
#include "mediaitem.h"

namespace BootPrints::Interfaces
{
    struct MediaItemReceived : public Plugin
    {
        virtual void newMediaItemReceived(MediaItem file);
    };
}

#define MediaItemReceived_iid "org.Akooos.BootPrints.MediaItemReceived"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::MediaItemReceived, MediaItemReceived_iid)

#endif // SHARE_H
