#ifndef CONFIGUI_H
#define CONFIGUI_H

#include "plugin.h"

namespace BootPrints::Interfaces
{
   template<class T>
   struct ConfigUI : Plugin
   {
       T* widget() const = 0;
   };
}


#endif // CONFIGUI_H
