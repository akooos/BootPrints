#ifndef GUIPLUGIN_H
#define GUIPLUGIN_H

#include "plugin.h"

namespace BootPrints
{
  namespace Interfaces
  {
    struct GUIPlugin : Plugin
    {
       virtual void init() = 0;
       virtual void dispose() = 0;
    };
  }
}

BOOTPRINTS_DECLARE_INTERFACE(GUIPlugin,Akooos.Hungary.BootPrints)



#endif // GUIPLUGIN_H
