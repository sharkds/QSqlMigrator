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
#include "../BasicTest/BasicTest.h"
#include "MysqlMigrator/MysqlMigrator.h"
#include "Helper/SqlStructureService.h"
#include "Commands/CreateTrigger.h"
#include "Commands/DropTrigger.h"
#include "Commands/CreateProcedure.h"
#include "Commands/DropProcedure.h"
#include "Structure/Trigger.h"
#include "Structure/Procedure.h"

#include "MysqlConfig.h"

#include "MigrationExecution/LocalSchemeMigrationExecutionContext.h"
#include "MigrationExecution/LocalSchemeMigrationExecutionService.h"
#include "LocalSchemeMigrator/LocalSchemeMigrator.h"
#include "LocalSchemeMigrator/LocalSchemeComparisonContext.h"
#include "LocalSchemeMigrator/LocalSchemeComparisonService.h"

#include <QString>
#include <QtTest>

using namespace Structure;
using namespace Migrations;
using namespace MigrationExecution;

#define MYSQL_STRUCTURE_DATABASE "mysql"
#define MYSQLTEST_DATABASE_NAME "qdb_migrator_test_db"

class MysqlTest : public BasicTest
{
    Q_OBJECT

public:
    MysqlTest();
private Q_SLOTS:
    void testCreateTrigger();
    void testDropTrigger();
    void testTriggerMigrations();
    void testCreateProcedure();
    void testDropProcedure();
    void testProcedureMigrations();
};

MysqlTest::MysqlTest()
    : BasicTest(MYSQL_DRIVERNAME, MYSQLTEST_DATABASE_NAME, &MysqlMigrator::buildContext, MYSQL_STRUCTURE_DATABASE,
                MYSQL_HOSTNAME, MYSQL_HOSTPORT, MYSQL_USERNAME, MYSQL_PASSWORD)
{
}

void MysqlTest::testCreateTrigger()
{
    Commands::CommandPtr command(
                new Commands::CreateTable(
                    Table::Builder("testtable1")
                    << Column("ID", Type::Integer, Column::Primary)
                    << Column("col2", Type(Type::String, 23))
                    ));

    Trigger trigger("testtrigger1", "testtable1", Trigger::Before, Trigger::Update, "SET @test_id=0");

    Commands::CommandPtr command2(new Commands::CreateTrigger(trigger));

    CommandExecution::CommandExecutionContext serviceContext(m_context->database(), m_context->migrationConfig(), m_context->helperRepository());
    CommandExecution::CommandExecutionService execution;
    execution.execute(command, m_context->commandServiceRepository(), serviceContext);
    execution.execute(command2, m_context->commandServiceRepository(), serviceContext);

    QStringList tables = m_context->database().tables(QSql::Tables);
    QVERIFY2(tables.contains("testtable1"), "testtable should be created during migration!");

    //check if trigger was created successfully
    Structure::Trigger realTrigger( m_context->helperRepository().sqlStructureService().getTriggerDefinition(trigger.name(), m_context->database()) );
    if (realTrigger.tableName() != trigger.tableName()) {
        qDebug() << "local scheme trigger table:" << trigger.tableName();
        qDebug() << "real scheme trigger table:" << realTrigger.tableName();
        QFAIL("real and local scheme trigger differ");
    }

    if (realTrigger.timingName() != trigger.timingName()) {
        qDebug() << "local scheme trigger time:" << trigger.timingName();
        qDebug() << "real scheme trigger time:" << realTrigger.timingName();
        QFAIL("real and local scheme trigger differ");
    }
    QVERIFY2(tables.contains("testtable1"), "testtable should be created during migration!");

    if (realTrigger.eventName() != trigger.eventName()) {
        qDebug() << "local scheme trigger event:" << trigger.eventName();
        qDebug() << "real scheme trigger event:" << realTrigger.eventName();
        QFAIL("real and local scheme trigger differ");
    }

    if (realTrigger.body() != trigger.body()) {
        qDebug() << "local scheme trigger body:" << trigger.body();
        qDebug() << "real scheme trigger body:" << realTrigger.body();
        QFAIL("real and local scheme trigger differ");
    }
}

void MysqlTest::testDropTrigger()
{
    Commands::CommandPtr command(
                new Commands::CreateTable(
                    Table::Builder("testtable2")
                    << Column("ID", Type::Integer, Column::Primary)
                    << Column("col2", Type(Type::String, 23))
                    ));
    Trigger trigger("testtrigger2", "testtable2", Trigger::Before, Trigger::Update, "SET @test_id=0");

    Commands::CommandPtr command2(new Commands::CreateTrigger(trigger));

    CommandExecution::CommandExecutionContext serviceContext(m_context->database(), m_context->migrationConfig(), m_context->helperRepository());
    CommandExecution::CommandExecutionService execution;
    execution.execute(command, m_context->commandServiceRepository(), serviceContext);
    execution.execute(command2, m_context->commandServiceRepository(), serviceContext);

    QStringList tables = m_context->database().tables(QSql::Tables);
    QVERIFY2(tables.contains("testtable2"), "testtable should be created during migration!");

    Structure::Trigger realTrigger( m_context->helperRepository().sqlStructureService().getTriggerDefinition(trigger.name(), m_context->database()) );
    QVERIFY2(realTrigger.tableName() == trigger.tableName(), "testtrigger should be created during migration!");

    Commands::CommandPtr command3(new Commands::DropTrigger("testtrigger2"));
    execution.execute(command3, m_context->commandServiceRepository(), serviceContext);
    Structure::Trigger realTrigger2( m_context->helperRepository().sqlStructureService().getTriggerDefinition(trigger.name(), m_context->database()) );
    QVERIFY2(!realTrigger2.isValid(), "testtrigger should be deleted during migration!");

    execution.execute(command2, m_context->commandServiceRepository(), serviceContext);
    Structure::Trigger realTrigger3( m_context->helperRepository().sqlStructureService().getTriggerDefinition(trigger.name(), m_context->database()) );
    QVERIFY2(realTrigger3.tableName() == trigger.tableName(), "testtrigger should be created during migration!");

    Commands::CommandPtr command4(new Commands::DropTrigger(trigger));
    execution.execute(command4, m_context->commandServiceRepository(), serviceContext);
    Structure::Trigger realTrigger4( m_context->helperRepository().sqlStructureService().getTriggerDefinition(trigger.name(), m_context->database()) );
    QVERIFY2(!realTrigger4.isValid(), "testtrigger should be deleted during migration!");

    // execute migrations on local scheme
    Migration migration;
    migration.add(command);
    migration.add(command2);
    migration.add(command3);
    const QString migrationNo1 = "Migration No1";
    QMap<QString, const Migration*> migrationMap;
    migrationMap[migrationNo1] = &migration;
    MigrationExecution::LocalSchemeMigrationExecutionService localSchemeMigrator;
    LocalSchemePtr localScheme(new Structure::LocalScheme); // database equivalent
    MigrationExecution::LocalSchemeMigrationExecutionContext localSchemeMigrationContext(migrationMap);
    localSchemeMigrationContext.setLocalScheme(localScheme);
    localSchemeMigrationContext.setLocalSchemeCommandServiceRepository(LocalSchemeMigrator::createCommandServiceRepository());
    bool success = localSchemeMigrator.execute(migrationNo1, localSchemeMigrationContext);
    QVERIFY2(success, "Migration should work!");

    // compare local scheme with database
    LocalSchemeMigrator::LocalSchemeComparisonContext comparisonContext(localScheme, m_context->helperRepository(), m_context->database());
    LocalSchemeMigrator::LocalSchemeComparisonService comparisonService;
    success = comparisonService.compareLocalSchemeWithDatabase(comparisonContext);
    QVERIFY2(success, "local scheme should be identical to actual database scheme");
}

void MysqlTest::testTriggerMigrations()
{
    // migrations
    Migration m;
    m.add(new Commands::CreateTable(
              Table::Builder("testtable3")
              << Column("ID", Type::Integer, Column::Primary)
              << Column("col2", Type(Type::String, 23))
              ));

    Trigger trigger("testtrigger3", "testtable3", Trigger::Before, Trigger::Update, "SET @test_id=0");

    Migration m2;
    m2.add(new Commands::CreateTrigger(trigger));

    const QString migrationNo1 = "Migration No1";
    const QString migrationNo2 = "Migration No2";
    QMap<QString, const Migration*> migrationMap;
    migrationMap[migrationNo1] = &m;
    migrationMap[migrationNo2] = &m2;

    bool success;

    // execute migrations on real database
    MigrationExecutionService migrator;
    MigrationExecutionContext::Builder migrationContextBuilder(migrationMap);
    migrationContextBuilder.setDatabase(m_context->database());

    MigrationExecutionContextPtr migrationContext = m_buildContext(migrationContextBuilder);

    success = migrator.execute(migrationNo1, *migrationContext);
    QVERIFY2(success, "Migration should work!");
    QStringList tables = m_context->database().tables(QSql::Tables);
    QVERIFY2(tables.contains("testtable3"), "testtable should be created during migration!");

    success = migrator.execute(migrationNo2, *migrationContext);
    QVERIFY2(success, "Migration should work!");
    Structure::Trigger realTrigger( m_context->helperRepository().sqlStructureService().getTriggerDefinition(trigger.name(), m_context->database()) );
    QVERIFY2(realTrigger.tableName() == trigger.tableName(), "testtrigger should be created during migration!");

    // execute migrations on local scheme
    MigrationExecution::LocalSchemeMigrationExecutionService localSchemeMigrator;
    LocalSchemePtr localScheme(new Structure::LocalScheme); // database equivalent
    MigrationExecution::LocalSchemeMigrationExecutionContext localSchemeMigrationContext(migrationMap);
    localSchemeMigrationContext.setLocalScheme(localScheme);
    localSchemeMigrationContext.setLocalSchemeCommandServiceRepository(LocalSchemeMigrator::createCommandServiceRepository());

    success = localSchemeMigrator.execute(migrationNo1, localSchemeMigrationContext);
    QVERIFY2(success, "Migration should work!");
    success = localSchemeMigrator.execute(migrationNo2, localSchemeMigrationContext);
    QVERIFY2(success, "Migration should work!");

    // compare local scheme with database
    LocalSchemeMigrator::LocalSchemeComparisonContext comparisonContext(localScheme, m_context->helperRepository(), m_context->database());
    LocalSchemeMigrator::LocalSchemeComparisonService comparisonService;
    success = comparisonService.compareLocalSchemeWithDatabase(comparisonContext);
    QVERIFY2(success, "local scheme should be identical to actual database scheme");
}

void MysqlTest::testCreateProcedure()
{
    Procedure procedure("testprocedure1", "BEGIN END", "IN _in int UNSIGNED, OUT _out int", Procedure::Invoker);
    Commands::CommandPtr command(new Commands::CreateProcedure(procedure));

    CommandExecution::CommandExecutionContext serviceContext(m_context->database(), m_context->migrationConfig(), m_context->helperRepository());
    CommandExecution::CommandExecutionService execution;
    execution.execute(command, m_context->commandServiceRepository(), serviceContext);

    //check if procedure was created successfully
    Structure::Procedure realProcedure( m_context->helperRepository().sqlStructureService().getProcedureDefinition(procedure.name(), m_context->database()) );
    if (realProcedure.parameters() != procedure.parameters()) {
        qDebug() << "local scheme procedure parameters:" << procedure.parameters();
        qDebug() << "real scheme procedure parameters:" << realProcedure.parameters();
        QFAIL("real and local scheme procedure differ");
    }

    if (realProcedure.securityName() != procedure.securityName()) {
        qDebug() << "local scheme procedure security:" << procedure.securityName();
        qDebug() << "real scheme procedure security:" << realProcedure.securityName();
        QFAIL("real and local scheme procedure differ");
    }

    if (realProcedure.body() != procedure.body()) {
        qDebug() << "local scheme procedure body:" << procedure.body();
        qDebug() << "real scheme procedure body:" << realProcedure.body();
        QFAIL("real and local scheme procedure differ");
    }
}

void MysqlTest::testDropProcedure()
{
    Procedure procedure("testprocedure2", "BEGIN END", "IN _in int UNSIGNED, OUT _out int", Procedure::Invoker);
    Commands::CommandPtr command(new Commands::CreateProcedure(procedure));
    Commands::CommandPtr command2(new Commands::DropProcedure("testprocedure2"));
    Commands::CommandPtr command3(new Commands::DropProcedure(procedure));

    CommandExecution::CommandExecutionContext serviceContext(m_context->database(), m_context->migrationConfig(), m_context->helperRepository());
    CommandExecution::CommandExecutionService execution;
    execution.execute(command, m_context->commandServiceRepository(), serviceContext);

    Structure::Procedure realProcedure( m_context->helperRepository().sqlStructureService().getProcedureDefinition(procedure.name(), m_context->database()) );
    QVERIFY2(realProcedure.body() == procedure.body(), "testprocedure should be created!");

    execution.execute(command2, m_context->commandServiceRepository(), serviceContext);
    Structure::Procedure realProcedure2( m_context->helperRepository().sqlStructureService().getProcedureDefinition(procedure.name(), m_context->database()) );
    QVERIFY2(!realProcedure2.isValid(), "testprocedure should be deleted!");

    execution.execute(command, m_context->commandServiceRepository(), serviceContext);
    Structure::Procedure realProcedure3( m_context->helperRepository().sqlStructureService().getProcedureDefinition(procedure.name(), m_context->database()) );
    QVERIFY2(realProcedure3.body() == procedure.body(), "testprocedure should be created!");

    execution.execute(command3, m_context->commandServiceRepository(), serviceContext);
    Structure::Procedure realProcedure4( m_context->helperRepository().sqlStructureService().getProcedureDefinition(procedure.name(), m_context->database()) );
    QVERIFY2(!realProcedure4.isValid(), "testprocedure should be deleted!");

    // execute migrations on local scheme
    Migration migration;
    migration.add(command);
    migration.add(command2);
    const QString migrationNo1 = "Migration No1";
    QMap<QString, const Migration*> migrationMap;
    migrationMap[migrationNo1] = &migration;
    MigrationExecution::LocalSchemeMigrationExecutionService localSchemeMigrator;
    LocalSchemePtr localScheme(new Structure::LocalScheme); // database equivalent
    MigrationExecution::LocalSchemeMigrationExecutionContext localSchemeMigrationContext(migrationMap);
    localSchemeMigrationContext.setLocalScheme(localScheme);
    localSchemeMigrationContext.setLocalSchemeCommandServiceRepository(LocalSchemeMigrator::createCommandServiceRepository());
    bool success = localSchemeMigrator.execute(migrationNo1, localSchemeMigrationContext);
    QVERIFY2(success, "Migration should work!");

    // compare local scheme with database
    LocalSchemeMigrator::LocalSchemeComparisonContext comparisonContext(localScheme, m_context->helperRepository(), m_context->database());
    LocalSchemeMigrator::LocalSchemeComparisonService comparisonService;
    success = comparisonService.compareLocalSchemeWithDatabase(comparisonContext);
    QVERIFY2(success, "local scheme should be identical to actual database scheme");
}

void MysqlTest::testProcedureMigrations()
{
    // migrations
    Procedure procedure("testprocedure3", "BEGIN END", "IN _in int UNSIGNED, OUT _out int", Procedure::Definer);
    Migration m;
    m.add(new Commands::CreateProcedure(procedure));

    const QString migrationNo1 = "Migration No1";
    QMap<QString, const Migration*> migrationMap;
    migrationMap[migrationNo1] = &m;

    bool success;

    // execute migrations on real database
    MigrationExecutionService migrator;
    MigrationExecutionContext::Builder migrationContextBuilder(migrationMap);
    migrationContextBuilder.setDatabase(m_context->database());

    MigrationExecutionContextPtr migrationContext = m_buildContext(migrationContextBuilder);

    success = migrator.execute(migrationNo1, *migrationContext);
    QVERIFY2(success, "Migration should work!");
    Structure::Procedure realProcedure( m_context->helperRepository().sqlStructureService().getProcedureDefinition(procedure.name(), m_context->database()) );
    QVERIFY2(realProcedure.body() == procedure.body(), "testprocedure should be created during migration!");

    // execute migrations on local scheme
    MigrationExecution::LocalSchemeMigrationExecutionService localSchemeMigrator;
    LocalSchemePtr localScheme(new Structure::LocalScheme); // database equivalent
    MigrationExecution::LocalSchemeMigrationExecutionContext localSchemeMigrationContext(migrationMap);
    localSchemeMigrationContext.setLocalScheme(localScheme);
    localSchemeMigrationContext.setLocalSchemeCommandServiceRepository(LocalSchemeMigrator::createCommandServiceRepository());

    success = localSchemeMigrator.execute(migrationNo1, localSchemeMigrationContext);
    QVERIFY2(success, "Migration should work!");

    // compare local scheme with database
    LocalSchemeMigrator::LocalSchemeComparisonContext comparisonContext(localScheme, m_context->helperRepository(), m_context->database());
    LocalSchemeMigrator::LocalSchemeComparisonService comparisonService;
    success = comparisonService.compareLocalSchemeWithDatabase(comparisonContext);
    QVERIFY2(success, "local scheme should be identical to actual database scheme");
}

QTEST_MAIN(MysqlTest)

#include "tst_MysqlTest.moc"
