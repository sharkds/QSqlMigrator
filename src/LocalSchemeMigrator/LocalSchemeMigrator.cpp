#include "LocalSchemeMigrator.h"

#include "LocalSchemeMigrator/CommandExecution/LocalSchemeAddColumnService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeAlterColumnTypeService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeCreateIndexService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeCreateProcedureService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeCreateTableService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeCreateTriggerService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeDropColumnService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeDropIndexService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeDropProcedureService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeDropTableService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeDropTriggerService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeRenameColumnService.h"
#include "LocalSchemeMigrator/CommandExecution/LocalSchemeRenameTableService.h"

#include "CommandExecution/LocalSchemeCommandExecutionServiceRepository.h"

namespace LocalSchemeMigrator {

QSharedPointer<CommandExecution::LocalSchemeCommandExecutionServiceRepository> createCommandServiceRepository()
{
    using namespace CommandExecution;

    QSharedPointer<LocalSchemeCommandExecutionServiceRepository> commandRepository(new LocalSchemeCommandExecutionServiceRepository);
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeAddColumnService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeAlterColumnTypeService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeCreateIndexService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeCreateProcedureService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeCreateTableService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeCreateTriggerService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeDropColumnService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeDropIndexService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeDropProcedureService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeDropTableService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeDropTriggerService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeRenameColumnService));
    commandRepository->add(LocalSchemeBaseCommandServicePtr(new LocalSchemeRenameTableService));

    return commandRepository;
}

} // namespace LocalSchemeMigrator
