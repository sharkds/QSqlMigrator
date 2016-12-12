#include "BaseSqlMigrator/CommandExecution/BaseSqlCreateProcedureService.h"

#include "Helper/SqlStructureService.h"
#include "Commands/CreateProcedure.h"

#include <QDebug>

namespace CommandExecution {

BaseSqlCreateProcedureService::BaseSqlCreateProcedureService()
{
}

const QString &BaseSqlCreateProcedureService::commandType() const
{
    return Commands::CreateProcedure::typeName();
}

bool BaseSqlCreateProcedureService::execute(const Commands::CreateProcedure &createProcedure, const CommandExecutionContext &context)
{
    Q_UNUSED(createProcedure)
    Q_UNUSED(context)
    return false;
}

bool BaseSqlCreateProcedureService::execute(const Commands::ConstCommandPtr &command,
                                        CommandExecution::CommandExecutionContext &context) const
{
    Q_UNUSED(command)
    Q_UNUSED(context)
    return false;
}

bool BaseSqlCreateProcedureService::isValid(const Commands::ConstCommandPtr &command,
                                        const CommandExecution::CommandExecutionContext &context) const
{
    Q_UNUSED(context);
    QSharedPointer<const Commands::CreateProcedure> createProcedure(command.staticCast<const Commands::CreateProcedure>());

    Structure::Procedure procedure( context.helperRepository().sqlStructureService().getProcedureDefinition(createProcedure->procedure().name(), context.database()) );
    if (procedure.isValid()) {
        ::qWarning() << "procedure allready exists!";
        return false;
    }

    if (!createProcedure->procedure().isValid()) {
        ::qWarning() << "to create a procedure it must be valid!";
        return false;
    }
    return true;
}

} // namespace CommandExecution
