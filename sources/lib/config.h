#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <QSettings>
#include <singleton.h>


#define PROPERTY(type,name)  ConfigEntry<type> name = { #name }
#define PROPERTY_WITH_DEFAULT(type,name,defaultValue)  ConfigEntry<type> name = { #name, defaultValue }
#define GROUPED_PROPERTY(type,group,name,defaultValue)  ConfigEntryWithGroup<type> name = { #group, #name, defaultValue }


namespace{
    std::unique_ptr<QSettings> settings = {nullptr};
}
template <class T>
struct ConfigEntry
{    
    //key in the config
    const QString name;
    //default value if entry does not exist
    const QVariant defaultValue;
    /**
     * @brief Construct an Observer templated class
     * @param name key in the config
     * @param defaultValue
     */
    ConfigEntry(
            const char *name,
            const QVariant &defaultValue = QVariant()
    ):
        name(QString(name)),
        defaultValue(defaultValue)
    {

    }
    /**
     * @brief Loads value from the config.
     */
    operator T()
    {
        const T t;
        return value(t);
    }
    /**
     * @brief Checks whether the given field exists in the config.
     * @returns True when config entry exists in the config.
     */
    operator bool() const
    {
        return hasValue();
    }
    /**
     * @brief Saves value to the config.
     */
    ConfigEntry<T> & operator=(const T& value)
    {
        setValue(value);
        return *this;
    }
    virtual bool hasValue()
    {

        return settings->contains(this->name);
    }
    virtual QVariant getValue()
    {

        return settings->value(this->name, this->defaultValue);
    }
    QString value(T t)  {
        Q_UNUSED(t)
        return getValue().toString();
    }
public slots:

    void setValue(const T& value)
    {

        settings->setValue(this->name,value);
        settings->sync();
    }
};

template <class T>
struct ConfigEntryWithGroup : public ConfigEntry<T>
{

    const QString group;
    /**
     * @brief Construct an Observer templated class
     * @param group group name in the config
     * @param name key in the config
     * @param defaultValue
     */
    ConfigEntryWithGroup(
            const char *group,
            const char *name,
            const QVariant &defaultValue = QVariant()
            ): ConfigEntry<T>(name,defaultValue),
        group(QString(group))
    {

    }
    ConfigEntryWithGroup<T> & operator=(const T& value)
    {
        return static_cast<ConfigEntryWithGroup&> ( ConfigEntry<T>::operator = ( value) );
    }
    bool hasValue()
    {

        settings->beginGroup(this->group);
        bool result = settings->contains(this->name);
        settings->endGroup();
        return result;
    }
    QVariant getValue()
    {

        settings->beginGroup(this->group);
        QVariant result = settings->value(this->name,this->defaultValue);
        settings->endGroup();
        return result;
    }
    void setValue(const T& value)
    {

        settings->beginGroup(group);
        settings->setValue(this->name,value);
        settings->sync();
        settings->endGroup();
    }
};

class Config : public Singleton<Config>
{

public:
    Config():Singleton<Config>()
    {
        if (!settings)
        {
            settings.reset( new QSettings() );
        }

    }
    PROPERTY(int,posx);
    PROPERTY(int,posy);
    GROUPED_PROPERTY(QString,db,dbHost,"Hello world%");

};

#define Conf Config::instance()

#endif // CONFIG_H
