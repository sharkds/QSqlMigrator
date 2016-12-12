#ifndef STRUCTURE_LOCALSCHEME_H
#define STRUCTURE_LOCALSCHEME_H

#include "config.h"

#include "Structure/Table.h"
#include "Structure/Index.h"
#include "Structure/Trigger.h"

#include <QMap>
#include <QSharedPointer>

namespace Structure {

class QSQLMIGRATOR_DLL_EXPORT LocalScheme
{
public:
    /*!
     * \brief internal Assignable version of Table
     */
    class Table : public Structure::Table
    {
    public:
        Table(const Table& other);
        Table(const Structure::Table& other);
        Table& operator =(const Table& other);
    };

    /*!
     * \brief internal Assignable version of Index
     */
    class Index : public Structure::Index
    {
    public:
        Index(const Index& other);
        Index(const Structure::Index& other);
        Index& operator =(const Index& other);
    };

    /*!
     * \brief internal Assignable version of Trigger
     */
    class Trigger : public Structure::Trigger
    {
    public:
        Trigger(const Trigger& other);
        Trigger(const Structure::Trigger& other);
        Trigger& operator =(const Trigger& other);
    };

    typedef QMap<QString, Table> TableMap;
    typedef QMap<QString, Index> IndexMap;
    typedef QMap<QString, Trigger> TriggerMap;

    LocalScheme();

    TableMap &tables();
    IndexMap &indices();
    TriggerMap &triggers();

    const Structure::Table* table(const QString& name) const;
    const Structure::Index* index(const QString& name) const;
    const Structure::Trigger* trigger(const QString& name) const;

    void createTable(const Structure::Table& table);
    void alterTable(const Structure::Table& table);
    void dropTable(const QString& tableName);

    void createIndex(const Structure::Index &index);
    void alterIndex(const Structure::Index &index);
    void dropIndex(const QString& indexName);

    void createTrigger(const Structure::Trigger &trigger);
    void dropTrigger(const QString& triggerName);

private:
    TableMap m_tables;
    IndexMap m_indices;
    TriggerMap m_triggers;
};

} // namespace Structure

typedef QSharedPointer<Structure::LocalScheme> LocalSchemePtr;

#endif // STRUCTURE_LOCALSCHEME_H
