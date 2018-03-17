#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>

using namespace std;


namespace BootPrints
{
    namespace
    {
        typedef unsigned int ExceptionCode;
        const ExceptionCode
            UnknownError = 0,
            CannotAddPluginError = 1;

        const QHash<ExceptionCode,QString> messages =
        {
            { UnknownError, "Unknown error!"}
        };

    }

    template <ExceptionCode ErrorCode>
    class Exception : QException
    {
        QString msg;
    public:

        Exception(
                const  std::initializer_list<QString> & ls = {}
        )
        {
            auto it = BootPrints::messages.find(ErrorCode);
            if ( it == messages.end() )
            {
                msg = messages[UnknownError];
            } else{
                msg = *it;
                for( const QString &item : ls)
                {
                    msg = msg.arg(item);
                }
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
            throw *this;
        }
        Exception *clone() const
        {
            return new Exception(*this);
        }
    };
    namespace Exceptions
    {
        typedef Exception<UnknownError> UnknownErrorExpcetion;
        typedef Exception<CannotAddPluginError> CannotAddPluginExpcetion;
    }
}
#endif // EXCEPTION_H
