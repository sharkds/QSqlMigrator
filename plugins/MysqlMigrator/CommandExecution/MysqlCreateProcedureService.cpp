#include "MysqlCreateProcedureService.h"

#include "Helper/QuoteService.h"
#include "Helper/SqlStructureService.h"

#include "MigrationTracker/MigrationTrackerService.h"

#include "Commands/CreateProcedure.h"

#include "Structure/Table.h"

#include <QDebug>
#include <QStringList>

namespace CommandExecution {

MysqlCreateProcedureService::MysqlCreateProcedureService()
{
}

bool MysqlCreateProcedureService::execute(const Commands::CreateProcedure &createProcedure, const CommandExecutionContext &context)
{
    const QString createQuery =
            QString("CREATE PROCEDURE %1 (%2)\n"
                    "    SQL SECURITY %3\n"
                    "%4")
            .arg(context.helperRepository().quoteService().quoteTableName(createProcedure.procedure().name()))
            .arg(createProcedure.procedure().parameters())
            .arg(createProcedure.procedure().securityName())
            .arg(createProcedure.procedure().body());

    return CommandExecution::BaseCommandExecutionService::executeQuery(createQuery, context);
}

bool MysqlCreateProcedureService::execute(const Commands::ConstCommandPtr &command,
                                        CommandExecution::CommandExecutionContext &context) const
{
    QSharedPointer<const Commands::CreateProcedure> createProcedure(command.staticCast<const Commands::CreateProcedure>());
    Q_ASSERT(createProcedure);

    bool success = execute(*createProcedure, context);

    if (success && context.isUndoUsed()) {
        context.setUndoCommand(createProcedure->reverse());
    }
    return success;
}

} // namespace CommandExecution
