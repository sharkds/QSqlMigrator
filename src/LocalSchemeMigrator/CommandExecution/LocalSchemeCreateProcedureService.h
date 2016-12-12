#ifndef COMMANDEXECUTION_LOCALSCHEMECREATEPROCEDURESERVICE_H
#define COMMANDEXECUTION_LOCALSCHEMECREATEPROCEDURESERVICE_H

#include "CommandExecution/LocalSchemeBaseCommandExecutionService.h"

namespace CommandExecution {

class QSQLMIGRATOR_DLL_EXPORT LocalSchemeCreateProcedureService : public LocalSchemeBaseCommandExecutionService
{
public:
    LocalSchemeCreateProcedureService();

    const QString &commandType() const;

    bool execute(const Commands::ConstCommandPtr &command,
                 CommandExecution::LocalSchemeCommandExecutionContext &context) const;

    bool isValid(const Commands::ConstCommandPtr &command,
                 const CommandExecution::LocalSchemeCommandExecutionContext &context) const;
};

} // namespace LocalSchemeCommandService

#endif // COMMANDEXECUTION_LOCALSCHEMECREATEPROCEDURESERVICE_H
