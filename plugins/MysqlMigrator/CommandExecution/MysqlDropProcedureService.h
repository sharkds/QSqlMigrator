#ifndef COMMANDEXECUTION_MYSQLDROPPROCEDURESERVICE_H
#define COMMANDEXECUTION_MYSQLDROPPROCEDURESERVICE_H

#include "MysqlMigrator/MysqlMigrator.h"

#include "BaseSqlMigrator/CommandExecution/BaseSqlDropProcedureService.h"

namespace Structure {
class Procedure;
} // namespace Structure

namespace CommandExecution {

class MYSQLMIGRATOR_DLL_EXPORT MysqlDropProcedureService : public BaseSqlDropProcedureService
{
public:
    MysqlDropProcedureService();
    ~MysqlDropProcedureService() QSQL_OVERRIDE_D {}

    static bool execute(const Commands::DropProcedure &dropProcedure, const CommandExecution::CommandExecutionContext &context);

    bool execute(const Commands::ConstCommandPtr &command, CommandExecution::CommandExecutionContext &context) const Q_DECL_OVERRIDE;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_MYSQLDROPPROCEDURESERVICE_H
