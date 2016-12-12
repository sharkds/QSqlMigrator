#ifndef COMMANDS_DROPTRIGGER_H
#define COMMANDS_DROPTRIGGER_H

#include "Commands/BaseCommand.h"
#include "Structure/Trigger.h"

namespace Commands {

/*!
 * \brief value object representing the command to drop a trigger
 */
class QSQLMIGRATOR_DLL_EXPORT DropTrigger : public BaseCommand
{
public:
    explicit DropTrigger(const QString &name);
    explicit DropTrigger(const Structure::Trigger &trigger);
    ~DropTrigger() QSQL_OVERRIDE_D {}

    static const QString &typeName();

    const Structure::Trigger &trigger() const;
    const QString &name() const;

    CommandPtr reverse() const Q_DECL_OVERRIDE;

private:
    const Structure::Trigger m_trigger;
};

inline const Structure::Trigger &DropTrigger::trigger() const
{
    return m_trigger;
}

inline const QString &DropTrigger::name() const
{
    return m_trigger.name();
}

} // namespace Commands

#endif // COMMANDS_DROPTRIGGER_H
