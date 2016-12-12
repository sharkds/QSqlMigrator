#ifndef COMMANDS_CREATEPROCEDURE_H
#define COMMANDS_CREATEPROCEDURE_H

#include "Commands/BaseCommand.h"
#include "Structure/Procedure.h"

namespace Commands {

/*!
 * \brief value object representing the command to create a procedure
 */
class QSQLMIGRATOR_DLL_EXPORT CreateProcedure : public BaseCommand
{
public:
    explicit CreateProcedure(const Structure::Procedure &procedure);
    ~CreateProcedure() QSQL_OVERRIDE_D {}

    static const QString &typeName();

    const Structure::Procedure &procedure() const;

    CommandPtr reverse() const Q_DECL_OVERRIDE;

private:
    const Structure::Procedure m_procedure;
};

inline const Structure::Procedure &CreateProcedure::procedure() const
{
    return m_procedure;
}

} // namespace Commands

#endif // COMMANDS_CREATEPROCEDURE_H
