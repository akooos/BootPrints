#include "dispatcherqt.h"
#include "bootprintsqt.h"

DispatcherQt::DispatcherQt(BootPrints::Interfaces::Plugin *plugin,
        const QJsonObject &metaData
) : Dispatcher(plugin,metaData)

{

}
const QIcon DispatcherQt::appIcon() const
{  
    return BootPrintsQt::instance()->mainWindow.windowIcon();
}


void DispatcherQt::quit()
{
    SCOPE_SENTINEL
   BootPrintsQt::instance()->quit();
}

void DispatcherQt::hide()
{
    BootPrintsQt::instance()->mainWindow.hide();
}

void DispatcherQt::show()
{
    BootPrintsQt::instance()->mainWindow.show();
}

bool DispatcherQt::isVisible() const
{
    return BootPrintsQt::instance()->mainWindow.isVisible();
}
