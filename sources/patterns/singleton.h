/**
 *  @brief Template of the Singleton programming pattern.
 *  @author Ákos Tóth
 */
#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
/**
 *  @brief Template of the Singleton programming pattern.
 *  @author Ákos Tóth
 */
template <class T, typename ...TArgs>
class Singleton
{
     static std::unique_ptr<T> _instance;
   public:

      static T & create(TArgs...args)
      {
          if( !_instance )
          {
              _instance.reset( new T(args...) );
          }
          return *_instance;
      }

      static T& instance()
      {
          return *_instance;
      }
   protected:
      Singleton(){}
   private:

      Singleton(const Singleton &) = delete;
      Singleton(const Singleton &&) = delete;
      Singleton &operator=(const Singleton &) = delete;
      Singleton &operator=(const Singleton &&) = delete;
};

template <class T, typename ...TArgs>
std::unique_ptr<T> Singleton<T,TArgs...>::_instance = nullptr;

#endif // SINGLETON_H
