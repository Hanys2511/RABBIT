DIR_NAME = "PROJECT"
QMAKE_PROJECT_NAME = $${DIR_NAME}
SOURCES += $$system("find $${DIR_NAME}/ -iname '*.cpp' -or -iname '*.hpp' -or -iname '*.h'")
DISTFILES += $$system("find $${DIR_NAME}/ -type f | grep -Pv '\.cpp' | grep -Pv '\.(h|hpp)'")
