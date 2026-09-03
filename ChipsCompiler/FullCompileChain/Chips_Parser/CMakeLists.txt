cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(ChipsParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ANTLR_JAR ${CMAKE_SOURCE_DIR}/antlr-4.13.2-complete.jar)
set(GRAMMAR  ${CMAKE_SOURCE_DIR}/Chips.g4)
set(GEN_DIR  ${CMAKE_SOURCE_DIR}/generated)
set(SRC_DIR  ${CMAKE_SOURCE_DIR}/sources)

file(MAKE_DIRECTORY ${GEN_DIR})

# Expected generated files (ANTLR output)
set(GEN_SOURCES
    ${GEN_DIR}/ChipsLexer.cpp
    ${GEN_DIR}/ChipsParser.cpp
    ${GEN_DIR}/ChipsBaseVisitor.cpp
    ${GEN_DIR}/ChipsVisitor.cpp
)

set(CHIPS_SOURCES
    ${SRC_DIR}/ast_definitions.cpp
    ${SRC_DIR}/ast_inoutputs.cpp
    ${SRC_DIR}/ast_lrxvalues.cpp
    ${SRC_DIR}/ast_program.cpp
    ${SRC_DIR}/ASTBuilder.cpp
    ${SRC_DIR}/utils.cpp
    ${SRC_DIR}/ast_builder_details.cpp
    ${SRC_DIR}/ChipsToXmiVisitor.cpp
    ${SRC_DIR}/ChipsToXmiWriter.cpp
)

add_custom_command(
    OUTPUT ${GEN_SOURCES}
    COMMAND java -jar ${ANTLR_JAR}
            -Dlanguage=Cpp
            -visitor
            -no-listener
            -o ${GEN_DIR}
            ${GRAMMAR}
    DEPENDS ${GRAMMAR}
)

add_custom_target(generate_antlr DEPENDS ${GEN_SOURCES})

add_executable(chipsparser
    ${GEN_SOURCES}
    ${CHIPS_SOURCES}
    ${CMAKE_SOURCE_DIR}/main.cpp
)

target_include_directories(chipsparser PRIVATE
    /usr/local/include/antlr4-runtime
    ${SRC_DIR}
    ${GEN_DIR}
)

target_link_libraries(chipsparser PRIVATE
    /usr/local/lib/libantlr4-runtime.so
)

add_dependencies(chipsparser generate_antlr)