#ifndef CONFIG_H
#define CONFIG_H

#include <common.h>

#include <QSettings>


#define CONFIG_MAIN_PROPERTY(type,name,args...) ConfigEntry<type> name = { #name, args }
#define CONFIG_GROUP(name) const QString config_group = name;
#define CONFIG_PROPERTY(type,name,args...)  GrouppedConfigEntry<type> name = { config_group, #name, args };

namespace
{
    QSettings settings = QSettings(BootPrints::org_name,BootPrints::app_name);
}

template <class T>
struct ConfigEntry
{    
    //key in the config
    const QString name;

    /**
     * @brief Construct an Observer templated class
     * @param name key in the config
     */
    ConfigEntry(
        const QString &name
    ):
        name(name)
    {

    }
    /**
     * @brief Loads value from the config.
     */
    operator T()
    {
        QVariant result = value();
        return result.value<T>();
    }
    /**
     * @brief Saves value to the config.
     */
    ConfigEntry<T> & operator=(const T& value)
    {
        setValue(value);
        return *this;
    }
    virtual bool exists() const
    {
        return settings.contains(this->name);
    }
    virtual QVariant value(QVariant defaultValue = QVariant()) const
    {
        return settings.value(this->name, defaultValue);
    }
    QString toString()
    {
        return value().toString();
    }
    virtual void setValue(const T& value)
    {
        settings.setValue(this->name,value);
        settings.sync();
    }
};

template <class T>
struct GrouppedConfigEntry : public ConfigEntry<T>
{
    const QString &group;
    /**
     * @brief Construct an Observer templated class
     * @param group group name in the config
     * @param name key in the config
     * @param defaultValue
     */
    GrouppedConfigEntry(
            const QString &group,
            const QString &name
            ): ConfigEntry<T>(name),
        group(group)
    {

    }
    GrouppedConfigEntry<T> & operator=(const T& value)
    {
        return static_cast<GrouppedConfigEntry&> ( ConfigEntry<T>::operator = ( value ) );
    }
    /**
     * @brief exists
     * @return
     */
    bool exists() const override
    {
        settings.beginGroup(this->group);
        bool result = settings.contains(this->name);
        settings.endGroup();
        return result;
    }
    QVariant value(QVariant defaultValue = QVariant()) const override
    {
        settings.beginGroup(this->group);
        QVariant result = settings.value(this->name,defaultValue);
        settings.endGroup();
        return result;
    }
    void setValue(const T& value) override
    {
        settings.beginGroup(group);
        settings.setValue(this->name,value);
        settings.sync();
        settings.endGroup();
    }
};

#endif // CONFIG_H
