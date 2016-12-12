#ifndef HELPER_SQLSTRUCTURESERVICE_H
#define HELPER_SQLSTRUCTURESERVICE_H

#include "config.h"
#include "Structure/Trigger.h"

#include <QString>
#include <QSqlDatabase>

namespace Structure {
class Table;
class Index;
} // namespace Structure

namespace Helper {

/*!
 * \brief interface for a service that extracts existing structures from a sql database
 */
class QSQLMIGRATOR_DLL_EXPORT SqlStructureService
{
public:
    virtual ~SqlStructureService() {}

    //! \return the definition of an existing table in the databse
    virtual Structure::Table getTableDefinition(const QString &tableName,
                                                QSqlDatabase database) const = 0;

    //! \return the definition of an existing index in the database for a table
    virtual Structure::Index getIndexDefinition(const QString &indexName,
                                                const QString &tableName,
                                                QSqlDatabase database) const = 0;

    //! \return the definition of an existing trigger in the database
    virtual Structure::Trigger getTriggerDefinition(const QString &triggerName,
                                                QSqlDatabase database) const {
        Q_UNUSED(database)
        // since it implemented only for MySQL, return empty Trigger
        // TODO implement Trigger in other databases
        return Structure::Trigger(triggerName, QString(), Structure::Trigger::After, Structure::Trigger::Insert, QString());
    }
};

} // namespace Helper

#endif // HELPER_SQLSTRUCTURESERVICE_H
