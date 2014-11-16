import qbs

Project {
  name: "QSqlMigrator"
  references: [
    'src/src.qbs',
    // 'plugins/FirebirdMigrator/FirebirdMigrator.qbs',
    // 'plugins/MysqlMigrator/MysqlMigrator.qbs',
    // 'plugins/PostgresqlMigrator/PostgresqlMigrator.qbs',
    'plugins/SqliteMigrator/SqliteMigrator.qbs',
    // 'tests/api/api.qbs',
    // 'tests/mysql/mysql.qbs',
    // 'tests/postgresql/postgresql.qbs',
    // 'tests/sqlite/sqlite.qbs'
  ]
}
