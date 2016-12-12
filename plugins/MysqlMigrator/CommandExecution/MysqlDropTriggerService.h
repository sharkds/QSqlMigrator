#ifndef COMMANDEXECUTION_MYSQLDROPTRIGGERSERVICE_H
#define COMMANDEXECUTION_MYSQLDROPTRIGGERSERVICE_H

#include "MysqlMigrator/MysqlMigrator.h"

#include "BaseSqlMigrator/CommandExecution/BaseSqlDropTriggerService.h"

namespace Structure {
class Trigger;
} // namespace Structure

namespace CommandExecution {

class MYSQLMIGRATOR_DLL_EXPORT MysqlDropTriggerService : public BaseSqlDropTriggerService
{
public:
    MysqlDropTriggerService();
    ~MysqlDropTriggerService() QSQL_OVERRIDE_D {}

    static bool execute(const Commands::DropTrigger &dropTrigger, const CommandExecution::CommandExecutionContext &context);

    bool execute(const Commands::ConstCommandPtr &command, CommandExecution::CommandExecutionContext &context) const Q_DECL_OVERRIDE;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_MYSQLDROPTRIGGERSERVICE_H
