#ifndef COMMANDEXECUTION_MYSQLCREATETRIGGERSERVICE_H
#define COMMANDEXECUTION_MYSQLCREATETRIGGERSERVICE_H

#include "MysqlMigrator/MysqlMigrator.h"

#include "BaseSqlMigrator/CommandExecution/BaseSqlCreateTriggerService.h"

namespace Structure {
class Trigger;
} // namespace Structure

namespace CommandExecution {

class MYSQLMIGRATOR_DLL_EXPORT MysqlCreateTriggerService : public BaseSqlCreateTriggerService
{
public:
    MysqlCreateTriggerService();
    ~MysqlCreateTriggerService() QSQL_OVERRIDE_D {}

    static bool execute(const Commands::CreateTrigger &createTrigger, const CommandExecution::CommandExecutionContext &context);

    bool execute(const Commands::ConstCommandPtr &command, CommandExecution::CommandExecutionContext &context) const Q_DECL_OVERRIDE;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_MYSQLCREATETRIGGERSERVICE_H
