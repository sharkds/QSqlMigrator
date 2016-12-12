#include "LocalSchemeMigrator/CommandExecution/LocalSchemeCreateTriggerService.h"

#include "Commands/CreateTrigger.h"
#include "Commands/DropTrigger.h"

#include <QDebug>
#include <QStringList>

namespace CommandExecution {

LocalSchemeCreateTriggerService::LocalSchemeCreateTriggerService()
{
}

const QString &LocalSchemeCreateTriggerService::commandType() const
{
    return Commands::CreateTrigger::typeName();
}

bool LocalSchemeCreateTriggerService::execute(const Commands::ConstCommandPtr &command,
                                            CommandExecution::LocalSchemeCommandExecutionContext &context) const
{
    QSharedPointer<const Commands::CreateTrigger> createTrigger(command.staticCast<const Commands::CreateTrigger>());

    context.localScheme()->createTrigger(createTrigger->trigger());

    return true;
}


bool LocalSchemeCreateTriggerService::isValid(const Commands::ConstCommandPtr &command,
                                            const CommandExecution::LocalSchemeCommandExecutionContext &context) const
{
    QSharedPointer<const Commands::CreateTrigger> createTrigger(command.staticCast<const Commands::CreateTrigger>());

    //check if table allready exists
    if (context.localScheme()->triggers().contains(createTrigger->trigger().name())) {
        ::qWarning() << "trigger allready exists!";
        return false;
    }

    //check if valid
    if (!createTrigger->trigger().isValid()) {
        ::qWarning() << "to create a trigger it must be valid!";
        return false;
    }
    return true;
}

} // namespace LocalSchemeCommandService
