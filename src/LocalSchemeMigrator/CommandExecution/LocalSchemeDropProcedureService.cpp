#include "LocalSchemeMigrator/CommandExecution/LocalSchemeDropProcedureService.h"

#include "Commands/DropProcedure.h"

#include <QDebug>
#include <QStringList>

namespace CommandExecution {

LocalSchemeDropProcedureService::LocalSchemeDropProcedureService()
{
}

const QString &LocalSchemeDropProcedureService::commandType() const
{
    return Commands::DropProcedure::typeName();
}

bool LocalSchemeDropProcedureService::execute(const Commands::ConstCommandPtr &command,
                                          CommandExecution::LocalSchemeCommandExecutionContext &context) const
{
    QSharedPointer<const Commands::DropProcedure> dropProcedure(command.staticCast<const Commands::DropProcedure>());

    context.localScheme()->dropProcedure(dropProcedure->name());

    return true;
}

bool LocalSchemeDropProcedureService::isValid(const Commands::ConstCommandPtr &command,
                                          const CommandExecution::LocalSchemeCommandExecutionContext &context) const
{
    Q_UNUSED(context);
    QSharedPointer<const Commands::DropProcedure> dropProcedure(command.staticCast<const Commands::DropProcedure>());

    if (dropProcedure->procedure().name().isEmpty()) {
        ::qWarning() << "name must be specified to drop a procedure!";
        return false;
    }

    //check if procedure exists
    if (!context.localScheme()->procedures().contains(dropProcedure->name())) {
        ::qWarning() << "procedure doesn't exist!";
        return false;
    }

    return true;
}

} // namespace CommandExecution
