import qbs

DynamicLibrary {
  name: "QSqlMigrator"
  targetName: "QSqlMigrator" + (qbs.buildVariant==='debug'?'d':'')
  version: "1.0.0"
  destinationDirectory: "bin"

  Depends { name: "cpp" }
  Depends { name: "Qt"; submodules: ["core", "sql"] }

  files: [ "**/*.cpp", "**/*.h", "../BasicTest.*" ]

  Group {
    fileTagsFilter: "dynamiclibrary"
    qbs.install: true
    qbs.installDir: product.destinationDirectory
  }

  cpp.includePaths: [ "." ]
  cpp.defines: ['_BUILDING_QSQLMIGRATOR_DLL', 'LOG_PREFIX="[QSqlMigrator]"']

  Properties {
    condition: cpp.compilerName.contains('g++')
    cpp.cxxFlags: ["-w", "-std=c++11"]
  }

  Export {
    Depends { name: "cpp" }
    cpp.includePaths: ['.']
    Properties {
        condition: cpp.compilerName.contains('g++')
        cpp.cxxFlags: ["-w", "-std=c++11"]
    }
  }
}
