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
template <class T>
class Singleton
{
      static std::unique_ptr<T> m_instance;

   protected:
      Singleton()
      {

      }

   public:

      static T & instance()
      {
          if( !m_instance )
          {
              m_instance.reset( new T() );
          }
          return *m_instance;
      }

      Singleton(const Singleton &) = delete;
      Singleton(const Singleton &&) = delete;
      Singleton &operator=(const Singleton &) = delete;
      Singleton &operator=(const Singleton &&) = delete;
};

template <class T>
std::unique_ptr<T> Singleton<T>::m_instance = nullptr;

#endif // SINGLETON_H
