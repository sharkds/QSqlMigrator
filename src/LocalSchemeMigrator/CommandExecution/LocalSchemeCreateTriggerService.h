#ifndef COMMANDEXECUTION_LOCALSCHEMECREATETRIGGERSERVICE_H
#define COMMANDEXECUTION_LOCALSCHEMECREATETRIGGERSERVICE_H

#include "CommandExecution/LocalSchemeBaseCommandExecutionService.h"

namespace CommandExecution {

class QSQLMIGRATOR_DLL_EXPORT LocalSchemeCreateTriggerService : public LocalSchemeBaseCommandExecutionService
{
public:
    LocalSchemeCreateTriggerService();

    const QString &commandType() const;

    bool execute(const Commands::ConstCommandPtr &command,
                 CommandExecution::LocalSchemeCommandExecutionContext &context) const;

    bool isValid(const Commands::ConstCommandPtr &command,
                 const CommandExecution::LocalSchemeCommandExecutionContext &context) const;
};

} // namespace LocalSchemeCommandService

#endif // COMMANDEXECUTION_LOCALSCHEMECREATETRIGGERSERVICE_H
