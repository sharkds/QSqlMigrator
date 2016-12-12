#include "MysqlCreateTriggerService.h"

#include "Helper/QuoteService.h"
#include "Helper/SqlStructureService.h"

#include "MigrationTracker/MigrationTrackerService.h"

#include "Commands/CreateTrigger.h"

#include "Structure/Table.h"

#include <QDebug>
#include <QStringList>

namespace CommandExecution {

MysqlCreateTriggerService::MysqlCreateTriggerService()
{
}

bool MysqlCreateTriggerService::execute(const Commands::CreateTrigger &createTrigger, const CommandExecutionContext &context)
{
    const QString createQuery =
            QString("CREATE TRIGGER %1 %2 %3 ON %4 FOR EACH ROW %5")
            .arg(context.helperRepository().quoteService().quoteTableName(createTrigger.trigger().name()))
            .arg(createTrigger.trigger().timingName())
            .arg(createTrigger.trigger().eventName())
            .arg(context.helperRepository().quoteService().quoteTableName(createTrigger.trigger().tableName()))
            .arg(createTrigger.trigger().body());

    return CommandExecution::BaseCommandExecutionService::executeQuery(createQuery, context);
}

bool MysqlCreateTriggerService::execute(const Commands::ConstCommandPtr &command,
                                        CommandExecution::CommandExecutionContext &context) const
{
    QSharedPointer<const Commands::CreateTrigger> createTrigger(command.staticCast<const Commands::CreateTrigger>());
    Q_ASSERT(createTrigger);

    bool success = execute(*createTrigger, context);

    if (success && context.isUndoUsed()) {
        context.setUndoCommand(createTrigger->reverse());
    }
    return success;
}

} // namespace CommandExecution
