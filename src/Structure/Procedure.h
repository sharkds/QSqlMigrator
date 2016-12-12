#ifndef STRUCTURE_PROCEDURE_H
#define STRUCTURE_PROCEDURE_H

#include "config.h"

#include <QString>

namespace Structure {

class QSQLMIGRATOR_DLL_EXPORT Procedure
{
public:
    enum Security {
        Definer,
        Invoker
    };

public:
    explicit Procedure(const QString &name, const QString &body,
                       const QString &parameters = "",
                       Security security = Security::Definer);

    const QString &name() const;
    const QString &parameters() const;
    const Security &security() const;
    QString securityName() const;
    const QString &body() const;

    bool isValid() const;

private:
    const QString m_name;
    const QString m_parameters;
    const Security m_security;
    const QString m_body;
};

} //namespace Structure

#endif // STRUCTURE_PROCEDURE_H
