#ifndef COMMANDEXECUTION_BASESQLDROPPROCEDURESERVICE_H
#define COMMANDEXECUTION_BASESQLDROPPROCEDURESERVICE_H

#include "CommandExecution/BaseCommandExecutionService.h"

namespace Commands {
class DropProcedure;
} // namespace Commands

namespace CommandExecution {

class QSQLMIGRATOR_DLL_EXPORT BaseSqlDropProcedureService : public BaseCommandExecutionService
{
public:
    BaseSqlDropProcedureService();

    const QString &commandType() const;

    static bool execute(const Commands::DropProcedure& dropProcedure, const CommandExecution::CommandExecutionContext &context);

    bool execute(const Commands::ConstCommandPtr &command,
                 CommandExecution::CommandExecutionContext &context) const;

    bool isValid(const Commands::ConstCommandPtr &command,
                 const CommandExecution::CommandExecutionContext &context) const;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_BASESQLDROPPROCEDURESERVICE_H
