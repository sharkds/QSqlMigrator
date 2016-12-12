#include "CreateTrigger.h"

#include "Commands/DropTrigger.h"

#include <QDebug>

namespace Commands {

CreateTrigger::CreateTrigger(const Structure::Trigger &trigger)
    : BaseCommand(CreateTrigger::typeName())
    , m_trigger(trigger)
{
    if( !m_trigger.isValid() ) {
        ::qWarning() << LOG_PREFIX << CreateTrigger::typeName() << "command with invalid trigger!";
    }
}

const QString &CreateTrigger::typeName()
{
    static QString typeName("CreateTrigger");
    return typeName;
}

CommandPtr CreateTrigger::reverse() const
{
    return CommandPtr(new DropTrigger(trigger()));
}

} // namespace Commands

