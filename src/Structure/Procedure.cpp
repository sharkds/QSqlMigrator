#include "Procedure.h"

#include <QDebug>

namespace Structure {

Procedure::Procedure(const QString &name, const QString &body, const QString &parameters, Security security)
    : m_name(name)
    , m_parameters(parameters)
    , m_security(security)
    , m_body(body)
{
    if(name.isEmpty()) {
        ::qWarning() << LOG_PREFIX << "Procedure with empty name!";
    }
}

const QString &Procedure::name() const
{
    return m_name;
}

const QString &Procedure::parameters() const
{
    return m_parameters;
}

const Procedure::Security &Procedure::security() const
{
    return m_security;
}

QString Procedure::securityName() const
{
    QString name;
    switch (m_security) {
    case Definer:
        name = "DEFINER";
        break;
    case Invoker:
        name = "INVOKER";
        break;
    }
    return name;
}

const QString &Procedure::body() const
{
    return m_body;
}

bool Procedure::isValid() const
{
    return !m_name.isEmpty() &&!m_body.isEmpty();
}

} //namespace Structure
