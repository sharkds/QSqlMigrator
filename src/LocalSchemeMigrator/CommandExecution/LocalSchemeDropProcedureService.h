#ifndef COMMANDEXECUTION_LOCALSCHEMEDROPPROCEDURESERVICE_H
#define COMMANDEXECUTION_LOCALSCHEMEDROPPROCEDURESERVICE_H

#include "CommandExecution/LocalSchemeBaseCommandExecutionService.h"

namespace CommandExecution {

class QSQLMIGRATOR_DLL_EXPORT LocalSchemeDropProcedureService : public LocalSchemeBaseCommandExecutionService
{
public:
    LocalSchemeDropProcedureService();

    const QString &commandType() const;

    bool execute(const Commands::ConstCommandPtr &command,
                 CommandExecution::LocalSchemeCommandExecutionContext &context) const;

    bool isValid(const Commands::ConstCommandPtr &command,
                 const CommandExecution::LocalSchemeCommandExecutionContext &context) const;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_LOCALSCHEMEDROPPROCEDURESERVICE_H
