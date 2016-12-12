#include "BaseSqlMigrator/CommandExecution/BaseSqlCreateTriggerService.h"

#include "Helper/SqlStructureService.h"
#include "Commands/CreateTrigger.h"

#include <QDebug>

namespace CommandExecution {

BaseSqlCreateTriggerService::BaseSqlCreateTriggerService()
{
}

const QString &BaseSqlCreateTriggerService::commandType() const
{
    return Commands::CreateTrigger::typeName();
}

bool BaseSqlCreateTriggerService::execute(const Commands::CreateTrigger &createTrigger, const CommandExecutionContext &context)
{
    Q_UNUSED(createTrigger)
    Q_UNUSED(context)
    return false;
}

bool BaseSqlCreateTriggerService::execute(const Commands::ConstCommandPtr &command,
                                        CommandExecution::CommandExecutionContext &context) const
{
    Q_UNUSED(command)
    Q_UNUSED(context)
    return false;
}

bool BaseSqlCreateTriggerService::isValid(const Commands::ConstCommandPtr &command,
                                        const CommandExecution::CommandExecutionContext &context) const
{
    Q_UNUSED(context);
    QSharedPointer<const Commands::CreateTrigger> createTrigger(command.staticCast<const Commands::CreateTrigger>());

    Structure::Trigger trigger( context.helperRepository().sqlStructureService().getTriggerDefinition(createTrigger->trigger().name(), context.database()) );
    if (trigger.isValid()) {
        ::qWarning() << "trigger allready exists!";
        return false;
    }

    if (!createTrigger->trigger().isValid()) {
        ::qWarning() << "to create a trigger it must be valid!";
        return false;
    }
    return true;
}

} // namespace CommandExecution
