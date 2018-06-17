#ifndef COMMON_H
#define COMMON_H

#include <QDebug>

#ifdef QT_DEBUG
    #include <QDateTime>
    #define DEBUG_MSG(s) qDebug() << QDateTime::currentDateTime().toString(Qt::DefaultLocaleShortDate) << "@" << __FILE__ << "#" << __LINE__ << "message:\"" << s << "\" in function: " << __PRETTY_FUNCTION__;
#else
    #define DEBUG_MSG(s)
#endif

#define STR(s) #s
#define STRINGIFY(s) STR(s)
#define DOT .
#define CONCAT(a,b,c,d) a##d##b##d##c
#define EVAL_CONCAT(a,b,c,d) CONCAT(a,b,c,d)

// V E R S I O N
#define MAJOR 0
#define MINOR 1
#define BUGFIX 0
#define APP_VERSION STRINGIFY(EVAL_CONCAT(MAJOR,MINOR,BUGFIX,DOT))
#define REVISION STRINGIFY(GIT_VERSION)

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
   static const char * app_name = "BootPrints";
   static const char * org_name = "BlueBlur";
   static const char * org_domain = "Software Development";
   static const char * version = APP_VERSION;
   static const char * build_date = __DATE__;
   static const char * build_time = __TIME__;
   static const char * compiler = COMPILER;
   static const char * sccs_version = STRINGIFY(GIT_VERSION);

}
#include "exception.h"
#endif // COMMON_H

