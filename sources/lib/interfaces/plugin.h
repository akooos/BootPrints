#ifndef PLUGIN_H
#define PLUGIN_H

#include <QStringList>

#define BOOTPRINTS_DECLARE_INTERFACE(name,id) \
    #define name##_iid #id \
    Q_DECLARE_INTERFACE(name, name##_iid);

namespace BootPrints{
  namespace Interfaces {
    struct Plugin{
       virtual void init() = 0;
       virtual void dispose() = 0;
       virtual QStringList dependencies()
       {
          return QStringList();
       }
    };
  }
}

#endif // PLUGIN_H
