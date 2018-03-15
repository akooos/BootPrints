#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#ifdef QT_DEBUG
    #include <QDateTime>
    #define DEBUG_MSG(s) qDebug() << QDateTime::currentDateTime().toString(Qt::DefaultLocaleShortDate) << "@" << __PRETTY_FUNCTION__ << "#" << __LINE__ << ":" << s;
#else
    #define DEBUG_MSG(s);
#endif

#endif // COMMON_H
