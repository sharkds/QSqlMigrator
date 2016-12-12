#ifndef COMMANDEXECUTION_MYSQLCREATEPROCEDURESERVICE_H
#define COMMANDEXECUTION_MYSQLCREATEPROCEDURESERVICE_H

#include "MysqlMigrator/MysqlMigrator.h"

#include "BaseSqlMigrator/CommandExecution/BaseSqlCreateProcedureService.h"

namespace Structure {
class Procedure;
} // namespace Structure

namespace CommandExecution {

class MYSQLMIGRATOR_DLL_EXPORT MysqlCreateProcedureService : public BaseSqlCreateProcedureService
{
public:
    MysqlCreateProcedureService();
    ~MysqlCreateProcedureService() QSQL_OVERRIDE_D {}

    static bool execute(const Commands::CreateProcedure &createProcedure, const CommandExecution::CommandExecutionContext &context);

    bool execute(const Commands::ConstCommandPtr &command, CommandExecution::CommandExecutionContext &context) const Q_DECL_OVERRIDE;
};

} // namespace CommandExecution

#endif // COMMANDEXECUTION_MYSQLCREATEPROCEDURESERVICE_H
