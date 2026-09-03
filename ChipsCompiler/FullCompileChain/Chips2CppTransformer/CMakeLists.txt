cmake_minimum_required(VERSION 3.20)

project(Chips2Cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ANTLR_VERSION 4.13.2)
set(ANTLR_JAR
"${CMAKE_CURRENT_SOURCE_DIR}/../Chips_Parser/antlr-${ANTLR_VERSION}-complete.jar"
)

set(ANTLR4_INCLUDE_DIR "/usr/local/include/antlr4-runtime")
set(ANTLR4_LIBRARY "/usr/local/lib/libantlr4-runtime.so")

set(GRAMMAR_FILE
"${CMAKE_CURRENT_SOURCE_DIR}/../Chips_Parser/Chips.g4"
)

set(GENERATED_DIR
"${CMAKE_CURRENT_BINARY_DIR}/generated"
)

find_package(Java REQUIRED COMPONENTS Runtime)

if(NOT EXISTS "${ANTLR_JAR}")
message(FATAL_ERROR "ANTLR JAR not found: ${ANTLR_JAR}")
endif()

if(NOT EXISTS "${GRAMMAR_FILE}")
message(FATAL_ERROR "ANTLR grammar not found: ${GRAMMAR_FILE}")
endif()

if(NOT EXISTS "${ANTLR4_INCLUDE_DIR}/antlr4-runtime.h")
message(FATAL_ERROR "ANTLR4 runtime headers not found")
endif()

if(NOT EXISTS "${ANTLR4_LIBRARY}")
message(FATAL_ERROR "ANTLR4 runtime library not found")
endif()


set(ANTLR_GENERATED_FILES
"${GENERATED_DIR}/ChipsLexer.cpp"
"${GENERATED_DIR}/ChipsLexer.h"
"${GENERATED_DIR}/ChipsParser.cpp"
"${GENERATED_DIR}/ChipsParser.h"
"${GENERATED_DIR}/ChipsBaseListener.cpp"
"${GENERATED_DIR}/ChipsBaseListener.h"
"${GENERATED_DIR}/ChipsListener.cpp"
"${GENERATED_DIR}/ChipsListener.h"
)

add_custom_command(
OUTPUT ${ANTLR_GENERATED_FILES}

```
COMMAND
    ${CMAKE_COMMAND} -E make_directory
    "${GENERATED_DIR}"

COMMAND
    ${Java_JAVA_EXECUTABLE}
    -jar "${ANTLR_JAR}"
    -Dlanguage=Cpp
    -listener
    -o "${GENERATED_DIR}"
    "${GRAMMAR_FILE}"

DEPENDS
    "${GRAMMAR_FILE}"
    "${ANTLR_JAR}"

COMMENT "Generating C++ parser with ANTLR ${ANTLR_VERSION}"
VERBATIM
```

)

find_path(ANTLR4_INCLUDE_DIR
    NAMES antlr4-runtime.h
    PATHS /usr/local/include
    NO_DEFAULT_PATH
)

find_library(ANTLR4_LIBRARY
    NAMES antlr4-runtime
    PATHS /usr/local/lib
    NO_DEFAULT_PATH
)

add_executable(Chips2Cpp
    src/main.cpp
    src/CodeGenListener.cpp
    ${ANTLR_GENERATED_FILES}
)


target_include_directories(Chips2Cpp
PRIVATE
"${ANTLR4_INCLUDE_DIR}"
"${GENERATED_DIR}"
)

target_link_libraries(Chips2Cpp
PRIVATE
"${ANTLR4_LIBRARY}"
)

set_target_properties(Chips2Cpp PROPERTIES
BUILD_RPATH "/usr/local/lib"
)