#ifndef COMMANDEXECUTION_BASESQLDROPTRIGGERSERVICE_H
#define COMMANDEXECUTION_BASESQLDROPTRIGGERSERVICE_H

#include "CommandExecution/BaseCommandExecutionService.h"

namespace Commands {
class DropTrigger;
} // namespace Commands

namespace CommandExecution {

class QSQLMIGRATOR_DLL_EXPORT BaseSqlDropTriggerService : public BaseCommandExecutionService
{
public:
    BaseSqlDropTriggerService();

    const QString &commandType() const;

    static bool execute(const Commands::DropTrigger& dropTrigger, const CommandExecution::CommandExecutionContext &context);

    bool execute(const Commands::ConstCommandPtr &command,
                 CommandExecution::CommandExecutionContext &context) const;

    bool isValid(const Commands::ConstCommandPtr &command,
                 const CommandExecution::CommandExecutionContext &context) const;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_BASESQLDROPTRIGGERSERVICE_H
