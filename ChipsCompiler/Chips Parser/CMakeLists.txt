cmake_minimum_required(VERSION 3.16)
project(ArithmeticInterpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Cherche la bibliothèque runtime ANTLR4 ────────────────────
# Option A : installée via apt / brew / vcpkg
find_package(antlr4-runtime QUIET)

if(antlr4-runtime_FOUND)
    message(STATUS "antlr4-runtime trouvé via find_package")
    set(ANTLR4_INCLUDE_DIRS ${ANTLR4_INCLUDE_DIR})
    set(ANTLR4_LIBS         antlr4_shared)
else()
    # Option B : chemin manuel (adapter si nécessaire)
    set(ANTLR4_INCLUDE_DIRS "/usr/local/include/antlr4-runtime"
                             "/usr/include/antlr4-runtime")
    find_library(ANTLR4_LIBS NAMES antlr4-runtime antlr4_shared
                 PATHS /usr/local/lib /usr/lib)
    if(NOT ANTLR4_LIBS)
        message(FATAL_ERROR
            "antlr4-runtime introuvable.\n"
            "Installer via : sudo apt install libantlr4-runtime-dev\n"
            "          ou : brew install antlr4-cpp-runtime")
    endif()
endif()

# ── Sources générées par ANTLR4 (après avoir lancé antlr4) ────
# Les fichiers sont générés dans <source_dir>/generated/, pas dans le build dir
set(ANTLR_GENERATED
    ${CMAKE_SOURCE_DIR}/generated/ChipsLexer.cpp
    ${CMAKE_SOURCE_DIR}/generated/ChipsParser.cpp
    ${CMAKE_SOURCE_DIR}/generated/ChipsBaseVisitor.cpp
    ${CMAKE_SOURCE_DIR}/generated/ChipsVisitor.cpp
)

# ── Cible principale ──────────────────────────────────────────
add_executable(chipsc
    main.cpp
    sources/chips_node_print.cpp
    sources/ChipsToXmiVisitor.cpp
    sources/ChipsToXmiWriter.cpp
    ${ANTLR_GENERATED}
)

target_include_directories(chipsc
    PRIVATE
        ${ANTLR4_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/generated/   # fichiers .h produits par ANTLR4
)

target_link_libraries(chipsc PRIVATE ${ANTLR4_LIBS})

# Warnings utiles
target_compile_options(chipsc PRIVATE -Wall -Wextra -Wpedantic)

# ── Cible pratique : génère les sources ANTLR4 ───────────────
find_program(ANTLR4_JAR_LAUNCHER java)
set(ANTLR4_JAR "${CMAKE_SOURCE_DIR}/antlr-4.13.1-complete.jar")

if(ANTLR4_JAR_LAUNCHER AND EXISTS "${ANTLR4_JAR}")
    add_custom_command(
        OUTPUT  ${ANTLR_GENERATED}
        COMMAND ${ANTLR4_JAR_LAUNCHER}
                -jar ${ANTLR4_JAR}
                -Dlanguage=Cpp
                -visitor
                -no-listener
                -o ${CMAKE_SOURCE_DIR}/generated
                ${CMAKE_SOURCE_DIR}/Chips.g4
        DEPENDS ${CMAKE_SOURCE_DIR}/Chips.g4
        COMMENT "Génération des sources ANTLR4..."
    )
    add_custom_target(generate_antlr DEPENDS ${ANTLR_GENERATED})
    add_dependencies(chipsc generate_antlr)
endif()