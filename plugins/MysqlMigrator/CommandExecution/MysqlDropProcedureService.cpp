#include "MysqlDropProcedureService.h"

#include "Helper/QuoteService.h"
#include "Helper/SqlStructureService.h"

#include "MigrationTracker/MigrationTrackerService.h"

#include "Commands/CreateProcedure.h"
#include "Commands/DropProcedure.h"

#include "Structure/Table.h"

#include <QDebug>
#include <QStringList>

namespace CommandExecution {

MysqlDropProcedureService::MysqlDropProcedureService()
{
}

bool MysqlDropProcedureService::execute(const Commands::DropProcedure &dropProcedure, const CommandExecutionContext &context)
{
    const QString sqlQuery = QString("DROP PROCEDURE %1").arg(dropProcedure.name());

    return CommandExecution::BaseCommandExecutionService::executeQuery(sqlQuery, context);
}

bool MysqlDropProcedureService::execute(const Commands::ConstCommandPtr &command,
                                        CommandExecution::CommandExecutionContext &context) const
{
    QSharedPointer<const Commands::DropProcedure> dropProcedure(command.staticCast<const Commands::DropProcedure>());
    Q_ASSERT(dropProcedure);

    const Structure::Procedure originalProcedure( context.helperRepository().sqlStructureService().getProcedureDefinition(dropProcedure->name(), context.database()) );

    bool success = execute(*dropProcedure, context);

    if (success && context.isUndoUsed()) {
        context.setUndoCommand(Commands::CommandPtr(new Commands::CreateProcedure(originalProcedure)));
    }
    return success;
}

} // namespace CommandExecution
