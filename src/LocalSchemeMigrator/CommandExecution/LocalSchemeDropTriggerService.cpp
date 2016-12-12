#include "LocalSchemeMigrator/CommandExecution/LocalSchemeDropTriggerService.h"

#include "Commands/DropTrigger.h"

#include <QDebug>
#include <QStringList>

namespace CommandExecution {

LocalSchemeDropTriggerService::LocalSchemeDropTriggerService()
{
}

const QString &LocalSchemeDropTriggerService::commandType() const
{
    return Commands::DropTrigger::typeName();
}

bool LocalSchemeDropTriggerService::execute(const Commands::ConstCommandPtr &command,
                                          CommandExecution::LocalSchemeCommandExecutionContext &context) const
{
    QSharedPointer<const Commands::DropTrigger> dropTrigger(command.staticCast<const Commands::DropTrigger>());

    context.localScheme()->dropTrigger(dropTrigger->name());

    return true;
}

bool LocalSchemeDropTriggerService::isValid(const Commands::ConstCommandPtr &command,
                                          const CommandExecution::LocalSchemeCommandExecutionContext &context) const
{
    Q_UNUSED(context);
    QSharedPointer<const Commands::DropTrigger> dropTrigger(command.staticCast<const Commands::DropTrigger>());

    if (dropTrigger->trigger().name().isEmpty()) {
        ::qWarning() << "name must be specified to drop a trigger!";
        return false;
    }

    //check if trigger exists
    if (!context.localScheme()->triggers().contains(dropTrigger->name())) {
        ::qWarning() << "trigger doesn't exist!";
        return false;
    }

    return true;
}

} // namespace CommandExecution
