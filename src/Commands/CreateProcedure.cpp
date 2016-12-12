#include "CreateProcedure.h"

#include "Commands/DropProcedure.h"

#include <QDebug>

namespace Commands {

CreateProcedure::CreateProcedure(const Structure::Procedure &procedure)
    : BaseCommand(CreateProcedure::typeName())
    , m_procedure(procedure)
{
    if( !m_procedure.isValid() ) {
        ::qWarning() << LOG_PREFIX << CreateProcedure::typeName() << "command with invalid procedure!";
    }
}

const QString &CreateProcedure::typeName()
{
    static QString typeName("CreateProcedure");
    return typeName;
}

CommandPtr CreateProcedure::reverse() const
{
    return CommandPtr(new DropProcedure(procedure()));
}

} // namespace Commands
