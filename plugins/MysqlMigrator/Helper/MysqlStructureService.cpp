/****************************************************************************
**
** Copyright (C) 2013, HicknHack Software
** All rights reserved.
** Contact: http://www.hicknhack-software.com/contact
**
** This file is part of the QSqlMigrator
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/
#include "MysqlMigrator/Helper/MysqlStructureService.h"

#include "MigrationTracker/MigrationTrackerService.h"

#include "CommandExecution/CommandExecutionContext.h"

#include "Structure/Table.h"
#include "Structure/Index.h"
#include "Structure/Trigger.h"
#include "Structure/Procedure.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>

using namespace Structure;

namespace Helper {

MysqlStructureService::MysqlStructureService()
{
}

Table MysqlStructureService::getTableDefinition(const QString &tableName, QSqlDatabase database) const
{
    ColumnList columns;
    do {
        QString queryString = QString("DESCRIBE %1").arg(tableName);
        QSqlQuery query = database.exec(queryString);
        QSqlError error = query.lastError();
        if (error.isValid()) {
            ::qDebug() << Q_FUNC_INFO << error.text();
            break;
        }
        while (query.next()) {
            QString name = query.value(0).toString();
            QString type = query.value(1).toString();
            bool null = (query.value(2).toString() == "YES") ? true : false;
            QString key = query.value(3).toString();
            QString defaultValue = query.value(4).toString();
            QString extra = query.value(5).toString();

            Column::Attributes attr = Column::None;
            if (!null) {
                attr |= Column::NotNullable;
            }
            if (key == "PRI") {
                attr |= Column::Primary;
            } else if (key == "UNI") {
                attr |= Column::Unique;
            }
            if (extra == "auto_increment") {
                attr |= Column::AutoIncrement;
            }

            //TODO: primary keys get default value set as 0?
            if (key == "PRI" && defaultValue == "0") {
                defaultValue = "";
            }
            columns << Column(name, type, defaultValue, attr);
        }
    } while (false);
    return Table(tableName, columns);
}

Index MysqlStructureService::getIndexDefinition(const QString &indexName,
                                                const QString &tableName,
                                                QSqlDatabase database) const
{
    Structure::Index::ColumnList columns;
    do {
        QString queryText = QString("SHOW INDEXES FROM %1 WHERE Key_name = \"%2\"").arg(tableName, indexName);
        ::qDebug() << "query looks like: " << queryText;
        QSqlQuery query = database.exec(queryText);
        QSqlError error = query.lastError();
        if (error.isValid()) {
            ::qDebug() << Q_FUNC_INFO << error.text();
            break;
        }
        while (query.next()) {
            columns << query.value(4).toString();
        }
    } while (false);
    return Structure::Index(indexName, tableName, columns);
}

Trigger MysqlStructureService::getTriggerDefinition(const QString &triggerName, QSqlDatabase database) const
{
    QString table;
    Trigger::Timing timing = Trigger::After;
    Trigger::Event event = Trigger::Insert;
    QString body;
    do {
        QString queryString = QString("SHOW TRIGGERS WHERE `Trigger` = \"%1\"").arg(triggerName);
        QSqlQuery query = database.exec(queryString);
        QSqlError error = query.lastError();
        if (error.isValid()) {
            ::qDebug() << Q_FUNC_INFO << error.text();
            break;
        }
        if (query.next()) {
            if (query.value(1).toString() == "INSERT") {
                event = Trigger::Insert;
            } else if (query.value(1).toString() == "DELETE") {
                event = Trigger::Delete;
            } else if (query.value(1).toString() == "UPDATE") {
                event = Trigger::Update;
            }
            table = query.value(2).toString();
            body = query.value(3).toString();
            if (query.value(4).toString() == "AFTER") {
                timing = Trigger::After;
            } else if (query.value(4).toString() == "BEFORE") {
                timing = Trigger::Before;
            }
        }
    } while (false);
    return Structure::Trigger(triggerName, table, timing, event, body);
}

Procedure MysqlStructureService::getProcedureDefinition(const QString &procedureName, QSqlDatabase database) const
{
    Procedure::Security security = Procedure::Definer;
    QString body, parameters;
    do {
        QString queryString = QString("SHOW CREATE PROCEDURE %1").arg(procedureName);
        QSqlQuery query = database.exec(queryString);
        QSqlError error = query.lastError();
        if (error.isValid()) {
            ::qDebug() << Q_FUNC_INFO << error.text();
            break;
        }
        if (query.next()) {
            QStringList procLines = query.value(2).toString().split("\n");

            QRegExp reParams("\\((.*)\\)");
            if (-1 != reParams.indexIn(procLines.value(0))) parameters = reParams.cap(1);
            if (!procLines.isEmpty()) procLines.removeFirst();

            while (procLines.value(0).startsWith("    ")) {
                if (procLines.value(0).endsWith("INVOKER")) {
                    security = Procedure::Invoker;
                }
                procLines.removeFirst();
            }

            body = procLines.join("\n");
        }
    } while (false);
    return Structure::Procedure(procedureName, body, parameters, security);
}

} // namespace Helper
