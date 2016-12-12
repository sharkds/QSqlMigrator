#ifndef COMMANDEXECUTION_BASESQLCREATETRIGGERSERVICE_H
#define COMMANDEXECUTION_BASESQLCREATETRIGGERSERVICE_H

#include "CommandExecution/BaseCommandExecutionService.h"

namespace Commands {
class CreateTrigger;
} // namespace Commands

namespace CommandExecution {

class QSQLMIGRATOR_DLL_EXPORT BaseSqlCreateTriggerService : public BaseCommandExecutionService
{
public:
    BaseSqlCreateTriggerService();

    const QString &commandType() const;

    static bool execute(const Commands::CreateTrigger &createTrigger, const CommandExecution::CommandExecutionContext &context);

    bool execute(const Commands::ConstCommandPtr &command, CommandExecution::CommandExecutionContext &context) const;
    bool isValid(const Commands::ConstCommandPtr &command, const CommandExecution::CommandExecutionContext &context) const;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_BASESQLCREATETRIGGERSERVICE_H
