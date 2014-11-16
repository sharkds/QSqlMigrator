import qbs

DynamicLibrary {
  name: "SqliteMigrator"
  targetName: "SqliteMigrator" + (qbs.buildVariant==='debug'?'d':'')
  version: "1.0.0"
  destinationDirectory: "bin/plugins"

  Depends { name: "cpp" }
  Depends { name: "Qt"; submodules: ["core", "sql"] }
  Depends { name: "QSqlMigrator" }

  files: [ "**/*.cpp", "**/*.h" ]

  Group {
    fileTagsFilter: "dynamiclibrary"
    qbs.install: true
    qbs.installDir: product.destinationDirectory
  }

  cpp.includePaths: [ ".." ]
  cpp.defines: ['_BUILDING_SQLITEMIGRATOR_DLL']

  Export {
    Depends { name: "cpp" }
    cpp.includePaths: ['..']
  }
}
