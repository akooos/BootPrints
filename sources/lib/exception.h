#ifndef BOOTPRINTS_EXCEPTION_H
#define BOOTPRINTS_EXCEPTION_H

#include <QException>
#include "common.h"

using namespace std;


namespace BootPrints
{
    namespace ExceptionCodes
    {
        enum ExceptionCode
        {
            UnknownError,
            CannotAddPluginError
        };
    }
    namespace
    {
        const QHash<ExceptionCodes::ExceptionCode,QString> messages =
        {
            { ExceptionCodes::UnknownError, "Error: \"%1\" "},
            { ExceptionCodes::CannotAddPluginError, "Could not add plugin: %1, %2"}
        };
    }

    class Exception : QException
    {
        ExceptionCodes::ExceptionCode ec;
        QString msg;
    public:

        static inline void fail(
            const ExceptionCodes::ExceptionCode ec = ExceptionCodes::UnknownError,
            const  std::initializer_list<QString> & ls = {}
        )
        {
            Exception e(ec,ls);
            e.raise();
        }
        Exception(
                const ExceptionCodes::ExceptionCode ec = ExceptionCodes::UnknownError,
                const  std::initializer_list<QString> & ls = {}
        )
        {
            auto it = BootPrints::messages.find(ec);
            if ( it == messages.end() )
            {
                msg = messages[ExceptionCodes::UnknownError];
            } else{
                msg = *it;
            }
            for( const QString &item : ls)
            {
                msg = msg.arg(item);
            }
        }
        operator QString() const
        {
            return this->toString();
        }
        QString toString() const
        {
            return msg;
        }
        void raise() const
        {
            DEBUG_MSG(this->toString())
            throw *this;
        }
        Exception *clone() const
        {
            return new Exception(*this);
        }
    };

}
#endif // BOOTPRINTS_EXCEPTION_H
