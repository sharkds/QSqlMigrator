#ifndef COMMANDS_DROPPROCEDURE_H
#define COMMANDS_DROPPROCEDURE_H

#include "Commands/BaseCommand.h"
#include "Structure/Procedure.h"

namespace Commands {

/*!
 * \brief value object representing the command to drop a procedure
 */
class QSQLMIGRATOR_DLL_EXPORT DropProcedure : public BaseCommand
{
public:
    explicit DropProcedure(const QString &name);
    explicit DropProcedure(const Structure::Procedure &procedure);
    ~DropProcedure() QSQL_OVERRIDE_D {}

    static const QString &typeName();

    const Structure::Procedure &procedure() const;
    const QString &name() const;

    CommandPtr reverse() const Q_DECL_OVERRIDE;

private:
    const Structure::Procedure m_procedure;
};

inline const Structure::Procedure &DropProcedure::procedure() const
{
    return m_procedure;
}

inline const QString &DropProcedure::name() const
{
    return m_procedure.name();
}

} // namespace Commands

#endif // COMMANDS_DROPPROCEDURE_H
