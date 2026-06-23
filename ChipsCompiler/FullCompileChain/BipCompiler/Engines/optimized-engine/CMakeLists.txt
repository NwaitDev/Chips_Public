cmake_minimum_required(VERSION 2.8)

PROJECT(BIP-optimized-engine)

if(NOT DEFINED VERSION)
  SET(VERSION "optimized")
endif(NOT DEFINED VERSION)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(NOT COMPILER_SUPPORTS_CXX0X)
  message(FATAL_ERROR "No support for C++0x in the C++ compiler (no option '-std=c++0x')!")
endif()

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "BIP Optimized Engine")
SET(CPACK_PACKAGE_VENDOR "VERIMAG")
SET(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${VERSION}_${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
# SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION}")
# SET(CPACK_PACKAGE_VERSION_MINOR )
# SET(CPACK_PACKAGE_VERSION_PATCH "3")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}-${VERSION}")
SET(CPACK_STRIP_FILES "lib/static/libengine.a")
SET(CPACK_SOURCE_STRIP_FILES "")

SET(CPACK_GENERATOR "TGZ")

INCLUDE(CPack)

configure_file( engine-version.hpp.in ${CMAKE_BINARY_DIR}/generated/engine-version.hpp )
include_directories( ${CMAKE_BINARY_DIR}/generated/ ) # Make sure it can be included...

# Select flags.
SET(CMAKE_CXX_FLAGS "-Wall -g -std=c++0x")
SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g -std=c++0x")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -std=c++0x")
SET(CMAKE_CXX_FLAGS_DEBUG  "-O0 -g -std=c++0x")
SET(CMAKE_CXX_FLAGS_PROFILING "-O0 -g -pg -std=c++0x")

include_directories("specific/include")
include_directories("generic/include")

SET(GENERIC_HEADER
  # this is the config file that maps abstract types used in engine to
  # real existing types.
  generic/include/bip-engineiface-config.hpp
  generic/include/bip-types.hpp

  generic/include/AtomItf.hpp  
  generic/include/ComponentItf.hpp
  generic/include/CompoundItf.hpp
  generic/include/AtomInternalPortItf.hpp
  generic/include/AtomExternalPortItf.hpp
  generic/include/AtomExportPortItf.hpp
  generic/include/AtomExportDataItf.hpp
  generic/include/ConnectorExportPortItf.hpp
  generic/include/ConnectorItf.hpp
  generic/include/InteractionItf.hpp
  generic/include/InteractionValueItf.hpp
  generic/include/PortItf.hpp
  generic/include/PortValueItf.hpp
  generic/include/QuotedPortReferenceItf.hpp
  generic/include/DataItf.hpp
  generic/include/PriorityItf.hpp
  generic/include/CompoundExportPortItf.hpp
  generic/include/CompoundExportDataItf.hpp
  generic/include/BipErrorItf.hpp
  generic/include/CycleInPrioritiesErrorItf.hpp
  generic/include/CycleInAtomPrioritiesErrorItf.hpp
  generic/include/NonDeterministicPetriNetErrorItf.hpp
  generic/include/NonOneSafePetriNetErrorItf.hpp
  generic/include/AtomInvariantViolationErrorItf.hpp
  generic/include/UnexpectedEventErrorItf.hpp
  generic/include/LauncherItf.hpp)



SET(GENERIC_SRC
  generic/src/AtomItf.cpp  
  generic/src/ComponentItf.cpp
  generic/src/CompoundItf.cpp
  generic/src/AtomInternalPortItf.cpp
  generic/src/AtomExternalPortItf.cpp
  generic/src/AtomExportPortItf.cpp
  generic/src/AtomExportDataItf.cpp
  generic/src/ConnectorExportPortItf.cpp
  generic/src/ConnectorItf.cpp
  generic/src/InteractionItf.cpp
  generic/src/InteractionValueItf.cpp
  generic/src/PortItf.cpp
  generic/src/PortValueItf.cpp
  generic/src/QuotedPortReferenceItf.cpp
  generic/src/DataItf.cpp
  generic/src/PriorityItf.cpp
  generic/src/CompoundExportPortItf.cpp
  generic/src/CompoundExportDataItf.cpp
  generic/src/BipErrorItf.cpp
  generic/src/CycleInPrioritiesErrorItf.cpp
  generic/src/CycleInAtomPrioritiesErrorItf.cpp
  generic/src/NonDeterministicPetriNetErrorItf.cpp
  generic/src/NonOneSafePetriNetErrorItf.cpp
  generic/src/AtomInvariantViolationErrorItf.cpp
  generic/src/UnexpectedEventErrorItf.cpp
  generic/src/LauncherItf.cpp)

SET(SPECIFIC_HEADER
  specific/include/Engine.hpp
  specific/include/Scheduler.hpp
  specific/include/ReferenceEngine.hpp
  specific/include/RandomScheduler.hpp
  specific/include/Explorer.hpp
  specific/include/State.hpp
  specific/include/StringTree.hpp
  specific/include/Resetable.hpp
  specific/include/Initializable.hpp

  specific/include/Atom.hpp
  specific/include/Component.hpp
  specific/include/Compound.hpp
  specific/include/AtomInternalPort.hpp
  specific/include/AtomExternalPort.hpp
  specific/include/AtomExportPort.hpp
  specific/include/AtomExportData.hpp
  specific/include/ConnectorExportPort.hpp
  specific/include/PortValue.hpp
  specific/include/Connector.hpp
  specific/include/Interaction.hpp
  specific/include/InteractionValue.hpp
  specific/include/Port.hpp
  specific/include/Data.hpp
  specific/include/Priority.hpp
  specific/include/CompoundExportPort.hpp
  specific/include/CompoundExportData.hpp
  specific/include/QuotedPortReference.hpp
  specific/include/BipError.hpp
  specific/include/CycleInPrioritiesError.hpp
  specific/include/CycleInAtomPrioritiesError.hpp
  specific/include/NonDeterministicPetriNetError.hpp
  specific/include/NonOneSafePetriNetError.hpp
  specific/include/AtomInvariantViolationError.hpp
  specific/include/UnexpectedEventError.hpp
  specific/include/CycleInPriorities.hpp
  specific/include/Launcher.hpp
  specific/include/Logger.hpp)

SET(SPECIFIC_SRC
  specific/src/Engine.cpp
  specific/src/Scheduler.cpp
  specific/src/ReferenceEngine.cpp
  specific/src/RandomScheduler.cpp
  specific/src/Explorer.cpp
  specific/src/State.cpp
  specific/src/StringTree.cpp
  specific/src/Resetable.cpp
  specific/src/Initializable.cpp

  specific/src/Atom.cpp
  specific/src/Component.cpp
  specific/src/Compound.cpp
  specific/src/AtomInternalPort.cpp
  specific/src/AtomExternalPort.cpp
  specific/src/AtomExportPort.cpp
  specific/src/AtomExportData.cpp
  specific/src/ConnectorExportPort.cpp
  specific/src/PortValue.cpp
  specific/src/Connector.cpp
  specific/src/Interaction.cpp
  specific/src/InteractionValue.cpp
  specific/src/Port.cpp
  specific/src/Data.cpp
  specific/src/Priority.cpp
  specific/src/CompoundExportPort.cpp
  specific/src/CompoundExportData.cpp
  specific/src/QuotedPortReference.cpp
  specific/src/BipError.cpp
  specific/src/CycleInPrioritiesError.cpp
  specific/src/CycleInAtomPrioritiesError.cpp
  specific/src/NonDeterministicPetriNetError.cpp
  specific/src/NonOneSafePetriNetError.cpp
  specific/src/AtomInvariantViolationError.cpp
  specific/src/UnexpectedEventError.cpp
  specific/src/CycleInPriorities.cpp
  specific/src/Launcher.cpp
  specific/src/Logger.cpp)

add_library(engine
  ${GENERIC_HEADER}
  ${GENERIC_SRC}
  ${SPECIFIC_HEADER}
  ${SPECIFIC_SRC}
)

# This is currently not used... but could be, in the future.
# set(ALL_HEADERS )
# list(APPEND ALL_HEADERS ${GENERIC_HEADER})
# list(APPEND ALL_HEADERS ${SPECIFIC_HEADER})

# set_target_properties(engine
#   PROPERTIES FRAMEWORK TRUE
#   PUBLIC_HEADER "${ALL_HEADERS}"
# )

install(TARGETS engine
   ARCHIVE DESTINATION lib/static)


install(FILES
  ${SPECIFIC_HEADER} DESTINATION include/specific)

install(FILES
  ${GENERIC_HEADER} DESTINATION include/generic)

