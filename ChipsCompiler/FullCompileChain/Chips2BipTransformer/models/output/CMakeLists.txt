cmake_minimum_required(VERSION 2.8)
# 2.8.3 has "CMAKE_CURRENT_LIST_DIR" variable. We have 2.8.2 deployed, 
# so using "CMAKE_SOURCE_DIR" instead.
set(GEN_ROOT ${CMAKE_SOURCE_DIR})

# Select flags.
SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x ")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g -std=c++0x ")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -std=c++0x ")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g -std=c++0x ")
SET(CMAKE_EXE_LINKER_FLAGS "")

SET(CMAKE_CXX_FLAGS_PROFILING "-O0 -g -pg")
SET(CMAKE_EXE_LINKER_FLAGS_PROFILING "-pg ")

# if none provided elsewhere, defaults to
# values from environment variables
IF(NOT BIP2_ENGINE_GENERIC_DIR)
  SET(BIP2_ENGINE_GENERIC_DIR $ENV{BIP2_ENGINE_GENERIC_DIR})
ENDIF()

IF(NOT BIP2_ENGINE_SPECIFIC_DIR)
  SET(BIP2_ENGINE_SPECIFIC_DIR $ENV{BIP2_ENGINE_SPECIFIC_DIR})
ENDIF()

IF(NOT BIP2_ENGINE_LIB_DIR)
  SET(BIP2_ENGINE_LIB_DIR $ENV{BIP2_ENGINE_LIB_DIR})
ENDIF()

include_directories(${BIP2_ENGINE_GENERIC_DIR})
include_directories(${BIP2_ENGINE_SPECIFIC_DIR})


# For package TeaStoreVariation
include_directories(${GEN_ROOT}/TeaStoreVariation/include)

add_subdirectory(${GEN_ROOT}/TeaStoreVariation)

set(CUSTOM_LIB_DIRS )

# Following only for building from instances.
