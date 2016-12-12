#include "Trigger.h"

#include <QDebug>

namespace Structure {

Trigger::Trigger(const QString &name, const QString &tableName, Timing timing, Event event, const QString &body)
    : m_name(name)
    , m_tableName(tableName)
    , m_timing(timing)
    , m_event(event)
    , m_body(body)
{
    if(name.isEmpty()) {
        ::qWarning() << LOG_PREFIX << "Trigger with empty name!";
    }
}

const QString &Trigger::name() const
{
    return m_name;
}

const QString &Trigger::tableName() const
{
    return m_tableName;
}

const Trigger::Timing &Trigger::timing() const
{
    return m_timing;
}

QString Trigger::timingName() const
{
    QString name;
    switch (m_timing) {
    case After:
        name = "AFTER";
        break;
    case Before:
        name = "BEFORE";
        break;
    }
    return name;
}

const Trigger::Event &Trigger::event() const
{
    return m_event;
}

QString Trigger::eventName() const
{
    QString name;
    switch (m_event) {
    case Insert:
        name = "INSERT";
        break;
    case Update:
        name = "UPDATE";
        break;
    case Delete:
        name = "DELETE";
        break;
    }
    return name;
}

const QString &Trigger::body() const
{
    return m_body;
}

bool Trigger::isValid() const
{
    return !m_name.isEmpty() && !m_tableName.isEmpty() && !m_body.isEmpty();
}

} //namespace Structure
