#ifndef UIINTERNAL_H
#define UIINTERNAL_H

#include <QAction>
#include <QIcon>

#include <QSharedPointer>

using QActionSPtr = QSharedPointer<QAction>;

struct UIInternal
{
    virtual const QIcon appIcon() const = 0;
    virtual void quit() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;
    virtual bool isVisible() const = 0;
};


#endif // UIINTERNAL_H
