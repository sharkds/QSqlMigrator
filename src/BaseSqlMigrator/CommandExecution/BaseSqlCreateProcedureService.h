#ifndef COMMANDEXECUTION_BASESQLCREATEPROCEDURESERVICE_H
#define COMMANDEXECUTION_BASESQLCREATEPROCEDURESERVICE_H

#include "CommandExecution/BaseCommandExecutionService.h"

namespace Commands {
class CreateProcedure;
} // namespace Commands

namespace CommandExecution {

class QSQLMIGRATOR_DLL_EXPORT BaseSqlCreateProcedureService : public BaseCommandExecutionService
{
public:
    BaseSqlCreateProcedureService();

    const QString &commandType() const;

    static bool execute(const Commands::CreateProcedure &createProcedure, const CommandExecution::CommandExecutionContext &context);

    bool execute(const Commands::ConstCommandPtr &command, CommandExecution::CommandExecutionContext &context) const;
    bool isValid(const Commands::ConstCommandPtr &command, const CommandExecution::CommandExecutionContext &context) const;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_BASESQLCREATEPROCEDURESERVICE_H
