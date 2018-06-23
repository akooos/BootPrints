#ifndef UIDISPATCHER_H
#define UIDISPATCHER_H

#include <dispatcher.h>
#include <uiinternal.h>

struct DispatcherQt : public Dispatcher, UIInternal
{
    DispatcherQt(
            BootPrints::Interfaces::Plugin *plugin,
            const QJsonObject &metaData
    );

    virtual const QIcon appIcon() const override;
    virtual void quit() override;
    virtual void show() override;
    virtual void hide() override;
    virtual bool isVisible() const;

};
#endif // UIDISPATCHER_H
