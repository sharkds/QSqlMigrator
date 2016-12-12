#include "DropTrigger.h"

#include "Commands/CreateTrigger.h"

#include <QDebug>

namespace Commands {

DropTrigger::DropTrigger(const QString &name)
    : BaseCommand(DropTrigger::typeName())
    , m_trigger(Structure::Trigger(name, QString(), Structure::Trigger::After, Structure::Trigger::Insert, QString()))
{
    if (name.isEmpty()) {
        ::qWarning() << LOG_PREFIX << DropTrigger::typeName() << "command with empty name!";
    }
}

DropTrigger::DropTrigger(const Structure::Trigger &trigger)
    : BaseCommand(DropTrigger::typeName())
    , m_trigger(trigger)
{
    if (m_trigger.name().isEmpty()) {
        ::qWarning() << LOG_PREFIX << DropTrigger::typeName() << "command with invalid trigger!";
    }
}

const QString &DropTrigger::typeName()
{
    static QString typeName("DropTrigger");
    return typeName;
}

CommandPtr DropTrigger::reverse() const
{
    if (!m_trigger.isValid())
        return CommandPtr();
    return CommandPtr(new CreateTrigger(trigger()));
}

} // namespace Commands
