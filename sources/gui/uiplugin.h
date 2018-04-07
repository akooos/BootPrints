#ifndef UIPLUGIN_H
#define UIPLUGIN_H

#include <QAction>
#include <QSharedPointer>
#include <QWidget>
#include <plugin.h>


using namespace BootPrints::Interfaces;

typedef QSharedPointer<QAction> QActionPtr;


struct UIPlugin : BasePlugin
{
    virtual const QIcon & appIcon() const = 0;
    virtual const QActionPtr actionClose() const = 0;

};

#endif // UIPLUGIN_H
