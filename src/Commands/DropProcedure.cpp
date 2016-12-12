#include "DropProcedure.h"

#include "Commands/CreateProcedure.h"

#include <QDebug>

namespace Commands {

DropProcedure::DropProcedure(const QString &name)
    : BaseCommand(DropProcedure::typeName())
    , m_procedure(Structure::Procedure(name, QString()))
{
    if (name.isEmpty()) {
        ::qWarning() << LOG_PREFIX << DropProcedure::typeName() << "command with empty name!";
    }
}

DropProcedure::DropProcedure(const Structure::Procedure &procedure)
    : BaseCommand(DropProcedure::typeName())
    , m_procedure(procedure)
{
    if (m_procedure.name().isEmpty()) {
        ::qWarning() << LOG_PREFIX << DropProcedure::typeName() << "command with invalid procedure!";
    }
}

const QString &DropProcedure::typeName()
{
    static QString typeName("DropProcedure");
    return typeName;
}

CommandPtr DropProcedure::reverse() const
{
    if (!m_procedure.isValid())
        return CommandPtr();
    return CommandPtr(new CreateProcedure(procedure()));
}

} // namespace Commands
