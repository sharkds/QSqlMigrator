#ifndef COMMANDS_CREATETRIGGER_H
#define COMMANDS_CREATETRIGGER_H

#include "Commands/BaseCommand.h"
#include "Structure/Trigger.h"

namespace Commands {

/*!
 * \brief value object representing the command to create a trigger
 */
class QSQLMIGRATOR_DLL_EXPORT CreateTrigger : public BaseCommand
{
public:
    explicit CreateTrigger(const Structure::Trigger &trigger);
    ~CreateTrigger() QSQL_OVERRIDE_D {}

    static const QString &typeName();

    const Structure::Trigger &trigger() const;

    CommandPtr reverse() const Q_DECL_OVERRIDE;

private:
    const Structure::Trigger m_trigger;
};

inline const Structure::Trigger &CreateTrigger::trigger() const
{
    return m_trigger;
}

} // namespace Commands

#endif // COMMANDS_CREATETRIGGER_H
