#ifndef COMMANDEXECUTION_LOCALSCHEMEDROPTRIGGERSERVICE_H
#define COMMANDEXECUTION_LOCALSCHEMEDROPTRIGGERSERVICE_H

#include "CommandExecution/LocalSchemeBaseCommandExecutionService.h"

namespace CommandExecution {

class QSQLMIGRATOR_DLL_EXPORT LocalSchemeDropTriggerService : public LocalSchemeBaseCommandExecutionService
{
public:
    LocalSchemeDropTriggerService();

    const QString &commandType() const;

    bool execute(const Commands::ConstCommandPtr &command,
                 CommandExecution::LocalSchemeCommandExecutionContext &context) const;

    bool isValid(const Commands::ConstCommandPtr &command,
                 const CommandExecution::LocalSchemeCommandExecutionContext &context) const;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_LOCALSCHEMEDROPTRIGGERSERVICE_H
