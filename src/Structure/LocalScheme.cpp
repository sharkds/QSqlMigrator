#include "LocalScheme.h"

#include <QDebug>

namespace Structure {

// Table
LocalScheme::Table::Table(const LocalScheme::Table &other)
    : Structure::Table( other.name(), other.columns() )
{
}

LocalScheme::Table::Table(const Structure::Table &other)
    : Structure::Table( other.name(), other.columns() )
{
}

LocalScheme::Table &LocalScheme::Table::operator =(const LocalScheme::Table &other)
{
    this->~Table();
    new(this) Table(other);
    return *this;
}

// Index
LocalScheme::Index::Index(const LocalScheme::Index &other)
    : Structure::Index( other.name(), other.tableName(), other.columns() )
{
}

LocalScheme::Index::Index(const Structure::Index &other)
    : Structure::Index( other.name(), other.tableName(), other.columns() )
{
}

LocalScheme::Index &LocalScheme::Index::operator =(const LocalScheme::Index &other)
{
    this->~Index();
    new(this) Index(other);
    return *this;
}

// Trigger
LocalScheme::Trigger::Trigger(const LocalScheme::Trigger &other)
    : Structure::Trigger( other.name(), other.tableName(), other.timing(), other.event(), other.body() )
{
}

LocalScheme::Trigger::Trigger(const Structure::Trigger &other)
    : Structure::Trigger( other.name(), other.tableName(), other.timing(), other.event(), other.body() )
{
}

LocalScheme::Trigger &LocalScheme::Trigger::operator =(const LocalScheme::Trigger &other)
{
    this->~Trigger();
    new(this) Trigger(other);
    return *this;
}

// LocalScheme
LocalScheme::LocalScheme()
{
}

LocalScheme::TableMap &LocalScheme::tables()
{
    return m_tables;
}

LocalScheme::IndexMap &LocalScheme::indices()
{
    return m_indices;
}

LocalScheme::TriggerMap &LocalScheme::triggers()
{
    return m_triggers;
}

const Structure::Table *LocalScheme::table(const QString &name) const
{
    auto it = m_tables.find(name);
    if (it == m_tables.end())
        return nullptr;
    return &it.value();
}

const Structure::Index *LocalScheme::index(const QString &name) const
{
    auto it = m_indices.find(name);
    if (it == m_indices.end())
        return nullptr;
    return &it.value();
}

const Structure::Trigger *LocalScheme::trigger(const QString &name) const
{
    auto it = m_triggers.find(name);
    if (it == m_triggers.end())
        return nullptr;
    return &it.value();
}

void LocalScheme::createTable(const Structure::Table &table)
{
    if (m_tables.contains(table.name())) {
        ::qWarning() << "Created table already existed" << table.name();
        return;
    }
    m_tables.insert( table.name(), table );
}

void LocalScheme::alterTable(const Structure::Table &table)
{
    int removed = m_tables.remove( table.name() );
    if (0 == removed) {
        ::qWarning() << "Altered table does not exist" << table.name();
    }
    m_tables.insert( table.name(), table );
}

void LocalScheme::dropTable(const QString &tableName)
{
    int removed = m_tables.remove( tableName );
    if (0 == removed) {
        ::qWarning() << "Dropped table does not exist" << tableName;
    }
}

void LocalScheme::createIndex(const Structure::Index &index)
{
    if (m_indices.contains(index.name())) {
        ::qWarning() << "Created index already existed" << index.name();
        return;
    }
    m_indices.insert( index.name(), index );
}

void LocalScheme::alterIndex(const Structure::Index &index)
{
    int removed = m_indices.remove( index.name() );
    if (0 == removed) {
        ::qWarning() << "Altered index does not exist" << index.name();
    }
    m_indices.insert( index.name(), index );
}

void LocalScheme::dropIndex(const QString &indexName)
{
    int removed = m_indices.remove( indexName );
    if (0 == removed) {
        ::qWarning() << "Dropped index does not exist" << indexName;
    }
}

void LocalScheme::createTrigger(const Structure::Trigger &trigger)
{
    if (m_triggers.contains(trigger.name())) {
        ::qWarning() << "Created trigger already existed" << trigger.name();
        return;
    }
    m_triggers.insert( trigger.name(), trigger );
}

void LocalScheme::dropTrigger(const QString &triggerName)
{
    int removed = m_triggers.remove( triggerName );
    if (0 == removed) {
        ::qWarning() << "Dropped trigger does not exist" << triggerName;
    }
}

} // namespace Structure
