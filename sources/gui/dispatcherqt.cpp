#include "dispatcherqt.h"
#include "bootprintsqt.h"

DispatcherQt::DispatcherQt(BootPrints::Interfaces::Plugin *plugin,
        const QJsonObject &metaData
) : Dispatcher(plugin,metaData)

{

}
const QIcon DispatcherQt::appIcon() const
{
    return BootPrintsQt::instance().mainWindow.windowIcon();
}

void DispatcherQt::quit()
{
   BootPrintsQt::instance().quit();
}
