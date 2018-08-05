#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#ifdef QT_DEBUG
    #include <QDateTime>
    #define DEBUG_MSG(s) qDebug() << __FILE__ << __LINE__ << s <<  __PRETTY_FUNCTION__ << QDateTime::currentDateTime().toSecsSinceEpoch();
#else
    #define DEBUG_MSG(s)
#endif

#define STR(s) #s
#define STRINGIFY(s) STR(s)
#define DOT .
#define CONCAT(a,b,c,d) a##d##b##d##c
#define EVAL_CONCAT(a,b,c,d) CONCAT(a,b,c,d)

// V E R S I O N
#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH 0000
#endif
#define MAJOR 0
#define MINOR 1
#define BUGFIX 0
#define APP_VERSION STRINGIFY(EVAL_CONCAT(MAJOR,MINOR,BUGFIX,DOT))
#define REVISION STRINGIFY(GIT_COMMIT_HASH)

#if defined(__clang__)
#define COMPILER "Clang/LLVM"

#elif defined(__ICC) || defined(__INTEL_COMPILER)
#define COMPILER "Intel ICC/ICPC"

#elif defined(__GNUC__) || defined(__GNUG__)
#define COMPILER "GNU GCC/G++"

#elif defined(__HP_cc) || defined(__HP_aCC)
#define COMPILER "Hewlett-Packard C/aC++"

#elif defined(__IBMC__) || defined(__IBMCPP__)
#define COMPILER "IBM XL C/C++"

#elif defined(_MSC_VER)
#define COMPILER "Microsoft Visual Studio"

#elif defined(__PGI)
#define COMPILER "Portland Group PGCC/PGCPP"

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define COMPILER "Oracle Solaris Studio"
#else
#define COMPILER "Unknown"
#endif

namespace BootPrints{
   extern const char app_name[];
   extern const char org_name[];
   extern const char org_domain[];
   extern const char version[];
   extern const char build_date[];
   extern const char build_time[];
   extern const char compiler[];
   extern const char sccs_version[];
}

#ifdef DEBUG_MSG
    struct ScopeChecker
    {
        QString funcname, file;
        int linenr;
        qint64 startTime;

        ScopeChecker( QString funcname, QString file, int linenr) : funcname(funcname),file(file),linenr(linenr), startTime(QDateTime::currentDateTime().toMSecsSinceEpoch())
        {
            qDebug() << ( QString("BEGIN %1 %2:%3 ").arg(funcname).arg(file).arg(linenr) ).toStdString().c_str() << startTime;

        }
        ~ScopeChecker()
        {
            qint64 endTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
            qDebug() << ( QString("END %1 %2:%3 ").arg(funcname).arg(file).arg(linenr) ).toStdString().c_str() <<  endTime;
            qDebug() << "Elapsed:" << ( endTime - startTime );
        }
    };
    #define SCOPE_SENTINEL ScopeChecker scopeChecker(__PRETTY_FUNCTION__,__FILE__,__LINE__);
#elif
#define SCOPE_CHECKER
#endif

#include "exception.h"
#endif // COMMON_H

