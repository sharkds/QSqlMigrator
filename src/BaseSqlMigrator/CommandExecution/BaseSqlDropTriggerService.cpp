#include "BaseSqlMigrator/CommandExecution/BaseSqlDropTriggerService.h"

#include "Helper/SqlStructureService.h"
#include "Commands/DropTrigger.h"

#include <QDebug>

namespace CommandExecution {

BaseSqlDropTriggerService::BaseSqlDropTriggerService()
{
}

const QString &BaseSqlDropTriggerService::commandType() const
{
    return Commands::DropTrigger::typeName();
}

bool BaseSqlDropTriggerService::execute(const Commands::DropTrigger &dropTrigger, const CommandExecutionContext &context)
{
    Q_UNUSED(dropTrigger)
    Q_UNUSED(context)
    return false;
}

bool BaseSqlDropTriggerService::execute(const Commands::ConstCommandPtr &command,
                                        CommandExecution::CommandExecutionContext &context) const
{
    Q_UNUSED(command)
    Q_UNUSED(context)
    return false;
}

bool BaseSqlDropTriggerService::isValid(const Commands::ConstCommandPtr &command,
                                        const CommandExecution::CommandExecutionContext &context) const
{
    Q_UNUSED(context);
    QSharedPointer<const Commands::DropTrigger> dropTrigger(command.staticCast<const Commands::DropTrigger>());

    if (dropTrigger->trigger().name().isEmpty()) {
        ::qWarning() << "name must be specified to drop a trigger!";
        return false;
    }

    Structure::Trigger trigger( context.helperRepository().sqlStructureService().getTriggerDefinition(dropTrigger->trigger().name(), context.database()) );
    if (!trigger.isValid()) {
        ::qWarning() << "trigger doesn't exist!";
        return false;
    }

    return true;
}

} // namespace CommandExecution
