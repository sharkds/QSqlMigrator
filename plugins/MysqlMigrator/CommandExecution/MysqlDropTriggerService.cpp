#include "MysqlDropTriggerService.h"

#include "Helper/QuoteService.h"
#include "Helper/SqlStructureService.h"

#include "MigrationTracker/MigrationTrackerService.h"

#include "Commands/CreateTrigger.h"
#include "Commands/DropTrigger.h"

#include "Structure/Table.h"

#include <QDebug>
#include <QStringList>

namespace CommandExecution {

MysqlDropTriggerService::MysqlDropTriggerService()
{
}

bool MysqlDropTriggerService::execute(const Commands::DropTrigger &dropTrigger, const CommandExecutionContext &context)
{
    const QString sqlQuery = QString("DROP TRIGGER %1").arg(dropTrigger.name());

    return CommandExecution::BaseCommandExecutionService::executeQuery(sqlQuery, context);
}

bool MysqlDropTriggerService::execute(const Commands::ConstCommandPtr &command,
                                        CommandExecution::CommandExecutionContext &context) const
{
    QSharedPointer<const Commands::DropTrigger> dropTrigger(command.staticCast<const Commands::DropTrigger>());
    Q_ASSERT(dropTrigger);

    const Structure::Trigger originalTrigger( context.helperRepository().sqlStructureService().getTriggerDefinition(dropTrigger->name(), context.database()) );

    bool success = execute(*dropTrigger, context);

    if (success && context.isUndoUsed()) {
        context.setUndoCommand(Commands::CommandPtr(new Commands::CreateTrigger(originalTrigger)));
    }
    return success;
}

} // namespace CommandExecution
