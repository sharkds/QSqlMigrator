#ifndef STRUCTURE_TRIGGER_H
#define STRUCTURE_TRIGGER_H

#include "config.h"

#include <QString>
#include <QList>

namespace Structure {

class QSQLMIGRATOR_DLL_EXPORT Trigger
{
public:
    enum Timing {
        After,
        Before
    };

    enum Event {
        Insert,
        Delete,
        Update
    };

public:   
    explicit Trigger(const QString &name, const QString &tableName, Timing timing, Event event, const QString &body);

    const QString &name() const;
    const QString &tableName() const;
    const Timing &timing() const;
    QString timingName() const;
    const Event &event() const;
    QString eventName() const;
    const QString &body() const;

    bool isValid() const;

private:
    const QString m_name;
    const QString m_tableName;
    const Timing m_timing;
    const Event m_event;
    const QString m_body;
};

} //namespace Structure

#endif // STRUCTURE_TRIGGER_H
