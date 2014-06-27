cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("ContributionC")
enable_testing()

find_package(Lua51 REQUIRED)

set(mySourceFiles
    src/c101_Company.c
    src/c101_Cut.c
    src/c101_Depth.c
    src/c101_Equal.c
    src/c101_Median.c
    src/c101_Parsing.c
    src/c101_Print.c
    src/c101_Subunit.c
    src/c101_Test.c
    src/c101_Total.c
    src/c101_Unparsing.c
    src/c101_Util.c
    src/c101_Vector.c
    src/c101_Visit.c
)

function(c101_add_test title)
    add_executable(${title} "test/${title}.c")
    target_link_libraries(${title} ${LUA_LIBRARY} 101)
    add_test(${title} ${title})
endfunction()

include_directories(include ${LUA_INCLUDE_DIR})

add_library(101 SHARED ${mySourceFiles})
target_link_libraries(101 ${LUA_LIBRARY})

add_executable(c101 src/main.c ${mySourceFiles})
target_link_libraries(c101 ${LUA_LIBRARY})

c101_add_test(totalTest)
c101_add_test(cutTest)
c101_add_test(medianTest)
c101_add_test(depthTest)
c101_add_test(equalTest)
c101_add_test(parsingTest)

set (luadir "${CMAKE_SOURCE_DIR}/lua")
file(COPY ${luadir}/dkjson.lua    DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${luadir}/dumper.lua    DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${luadir}/parsing.lua   DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${luadir}/sample.lua    DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${luadir}/unparsing.lua DESTINATION ${CMAKE_BINARY_DIR})

set(myGnuFlags "-Wall -Wextra -Wshadow -pedantic -pedantic-errors")

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 ${myGnuFlags}")
endif()

