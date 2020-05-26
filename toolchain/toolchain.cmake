INCLUDE(CMakeForceCompiler)
SET(CMAKE_SYSTEM_NAME Generic)

SET(CWD ${CMAKE_CURRENT_LIST_DIR})
EXECUTE_PROCESS(COMMAND ${CWD}/main.sh path OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE PATH)
EXECUTE_PROCESS(COMMAND ${CWD}/main.sh target OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE TARGET)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

SET(CMAKE_FIND_ROOT_PATH ${PATH})
SET(CMAKE_C_COMPILER ${PATH}/${TARGET}-gcc)
SET(CMAKE_CXX_COMPILER ${PATH}/${TARGET}-g++)

SET(CMAKE_SYSROOT ${CMAKE_INSTALL_PREFIX}/sysroot)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -isystem=/usr/include")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem=/usr/include")

SET(CMAKE_CROSSCOMPILING TRUE)
SET(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
