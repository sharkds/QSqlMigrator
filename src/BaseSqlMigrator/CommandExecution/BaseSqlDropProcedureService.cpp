#include "BaseSqlMigrator/CommandExecution/BaseSqlDropProcedureService.h"

#include "Helper/SqlStructureService.h"
#include "Commands/DropProcedure.h"

#include <QDebug>

namespace CommandExecution {

BaseSqlDropProcedureService::BaseSqlDropProcedureService()
{
}

const QString &BaseSqlDropProcedureService::commandType() const
{
    return Commands::DropProcedure::typeName();
}

bool BaseSqlDropProcedureService::execute(const Commands::DropProcedure &dropProcedure, const CommandExecutionContext &context)
{
    Q_UNUSED(dropProcedure)
    Q_UNUSED(context)
    return false;
}

bool BaseSqlDropProcedureService::execute(const Commands::ConstCommandPtr &command,
                                        CommandExecution::CommandExecutionContext &context) const
{
    Q_UNUSED(command)
    Q_UNUSED(context)
    return false;
}

bool BaseSqlDropProcedureService::isValid(const Commands::ConstCommandPtr &command,
                                        const CommandExecution::CommandExecutionContext &context) const
{
    Q_UNUSED(context);
    QSharedPointer<const Commands::DropProcedure> dropProcedure(command.staticCast<const Commands::DropProcedure>());

    if (dropProcedure->procedure().name().isEmpty()) {
        ::qWarning() << "name must be specified to drop a procedure!";
        return false;
    }

    Structure::Procedure procedure( context.helperRepository().sqlStructureService().getProcedureDefinition(dropProcedure->procedure().name(), context.database()) );
    if (!procedure.isValid()) {
        ::qWarning() << "procedure doesn't exist!";
        return false;
    }

    return true;
}

} // namespace CommandExecution
