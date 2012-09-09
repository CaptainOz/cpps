# cpps library build script

find_package( FLEX )
find_package( BISON )

BISON_TARGET(
    CPPSParser
    ${CMAKE_CURRENT_LIST_DIR}/cpps/cpps.y
    ${CMAKE_CURRENT_LIST_DIR}/cpps/cpps.tab.cpp
)
FLEX_TARGET(
    CPPSScanner
    ${CMAKE_CURRENT_LIST_DIR}/cpps/cpps.l
    ${CMAKE_CURRENT_LIST_DIR}/cpps/cpps.lex.cpp
)
ADD_FLEX_BISON_DEPENDENCY( CPPSScanner CPPSParser )

set( CPPS_SRC
    cpps/cpps.cpp
    ${BISON_CPPSParser_OUTPUTS}
    ${FLEX_CPPSScanner_OUTPUTS}
)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
)

add_executable( cpps ${CPPS_SRC} )
