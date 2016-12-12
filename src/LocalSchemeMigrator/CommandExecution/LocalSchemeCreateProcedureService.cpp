#include "LocalSchemeMigrator/CommandExecution/LocalSchemeCreateProcedureService.h"

#include "Commands/CreateProcedure.h"

#include <QDebug>
#include <QStringList>

namespace CommandExecution {

LocalSchemeCreateProcedureService::LocalSchemeCreateProcedureService()
{
}

const QString &LocalSchemeCreateProcedureService::commandType() const
{
    return Commands::CreateProcedure::typeName();
}

bool LocalSchemeCreateProcedureService::execute(const Commands::ConstCommandPtr &command,
                                            CommandExecution::LocalSchemeCommandExecutionContext &context) const
{
    QSharedPointer<const Commands::CreateProcedure> createProcedure(command.staticCast<const Commands::CreateProcedure>());

    context.localScheme()->createProcedure(createProcedure->procedure());

    return true;
}


bool LocalSchemeCreateProcedureService::isValid(const Commands::ConstCommandPtr &command,
                                            const CommandExecution::LocalSchemeCommandExecutionContext &context) const
{
    QSharedPointer<const Commands::CreateProcedure> createProcedure(command.staticCast<const Commands::CreateProcedure>());

    //check if table allready exists
    if (context.localScheme()->procedures().contains(createProcedure->procedure().name())) {
        ::qWarning() << "procedure allready exists!";
        return false;
    }

    //check if valid
    if (!createProcedure->procedure().isValid()) {
        ::qWarning() << "to create a procedure it must be valid!";
        return false;
    }
    return true;
}

} // namespace LocalSchemeCommandService
