#ifndef SHARE_H
#define SHARE_H

#include "plugin.h"

class QUrl;

namespace BootPrints::Interfaces
{
    struct Share : public Plugin
    {
        virtual void newShareReceived(const QUrl &url) = 0 ;
    };
}

#define Share_iid "org.Akooos.BootPrints.Share"
Q_DECLARE_INTERFACE(BootPrints::Interfaces::Share, Share_iid)

#endif // SHARE_H
