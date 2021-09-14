cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(name CaTS)
#add_compile_options(-std=c++17)
#set(CMAKE_CXX_STANDARD 17)
project(${name} VERSION 0.1.0)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})
#----------------------------------------------------------------------------
# CaTS requires shared libraries
#
if(NOT Geant4_shared_FOUND)
  message(FATAL_ERROR "CaTS must use shared libraries")
endif()


#target_compile_definitions(CaTS PRIVATE  WITH_G4OPTICKS=ON)
#add_compile_definitions(WITH_G4OPTICKS=1)
#add_definitions(WITH_G4OPTICKS "Build example with OPTICKS" ON)
option(WITH_ROOT "Build example with ROOT" ON)
option(WITH_G4OPTICKS "Build example with OPTICKS" ON)
option(G4ANALYSIS_USE "Build example with Analysis" ON)
if(G4ANALYSIS_USE)
 message(STATUS "G4ANALYSIS_USE is set")
endif()
if(WITH_G4OPTICKS)
include(OpticksBuildOptions)
find_package( G4OK CONFIG REQUIRED )
else()
message(STATUS "WITH_G4OPTICKS is not set")
include(CaTSCXXFlags)
endif()
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(WITH_ROOT)
  find_package(ROOT REQUIRED)
# ROOT version 6 required
if(ROOT_FOUND)
  STRING(REGEX MATCH "6.*" VERSION6MATCH ${ROOT_VERSION})
  if(NOT VERSION6MATCH)
    message(FATAL_ERROR "${name} requires ROOT 6")
  endif()
endif()
# Include ROOT's CMake functions for dictionary generation
#  since root6.20, the file is renamed and included by default, so include
#  only when we find the *old* name
if(EXISTS "${ROOT_DIR}/modules/RootNewMacros.cmake")
   include("${ROOT_DIR}/modules/RootNewMacros.cmake")
endif()
endif()
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
if(WITH_ROOT)
#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR}
                    ${ROOT_INCLUDE_DIRS})
#----------------------------------------------------------------------------
# Generate dictionaries, add ROOT libraries properties
#
REFLEX_GENERATE_DICTIONARY(CaTSClasses include/CaTSClasses.hh SELECTION xml/selection.xml)
add_library(CaTSClassesDict SHARED ${sources} CaTSClasses.cxx)
set(libsuffix .so)
set(ROOT_LIBRARY_PROPERTIES ${ROOT_LIBRARY_PROPERTIES} SUFFIX ${libsuffix})
set_target_properties(CaTSClassesDict PROPERTIES ${ROOT_LIBRARY_PROPERTIES})

#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

target_link_libraries(CaTSClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
else()
include_directories(${PROJECT_SOURCE_DIR}/include
  ${Geant4_INCLUDE_DIR})
endif()

file(GLOB detectors ${PROJECT_SOURCE_DIR}/gdml/*.gdml)
file(GLOB schemas ${PROJECT_SOURCE_DIR}/gdml/*.xsd)
file(GLOB scripts ${PROJECT_SOURCE_DIR}/scripts/*)
file(GLOB macros ${PROJECT_SOURCE_DIR}/macros/*.mac)
file(GLOB grid ${PROJECT_SOURCE_DIR}/grid/*)
file(GLOB evtdata ${PROJECT_SOURCE_DIR}/data/*)
file(GLOB runscripts ${PROJECT_SOURCE_DIR}/scripts/run.sh  ${PROJECT_SOURCE_DIR}/scripts/check.sh)

add_executable(${name} ${name}.cc ${sources} ${headers})
target_compile_definitions( ${name} PRIVATE WITH_G4OPTICKS WITH_ROOT)
if(WITH_G4OPTICKS)
target_link_libraries(${name}  CaTSClassesDict Opticks::G4OK ${Geant4_LIBRARIES} ${ROOT_LIBRARIES}  )
else()
target_link_libraries(${name}  CaTSClassesDict ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )
endif()
if(WITH_ROOT)
add_executable(readPhotonHits readPhotonHits.cc  ${sources} ${headers})
target_link_libraries(readPhotonHits CaTSClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )
add_executable(readCalorimeterHits  readCalorimeterHits.cc   ${sources} ${headers})
target_link_libraries(readCalorimeterHits CaTSClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )
add_executable(readMscHits readMscHits.cc  ${sources} ${headers})
target_link_libraries(readMscHits CaTSClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )
add_executable(readDRCalorimeterHits  readDRCalorimeterHits.cc   ${sources} ${headers})
target_link_libraries(readDRCalorimeterHits CaTSClassesDict  ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} )
link_directories( ${ROOT_LIBRARY_DIR} )
endif()

install(TARGETS ${name} DESTINATION bin)
install(FILES ${detectors} ${schemas}  ${scripts} ${macros} ${grid} ${evtdata} DESTINATION bin)
install(FILES ${detectors} DESTINATION bin/gdml)
install(FILES ${macros} DESTINATION bin/macros)
install(PROGRAMS ${runscripts}  DESTINATION bin)
if(WITH_ROOT)
  install(TARGETS CaTSClassesDict DESTINATION bin)
  install(TARGETS readPhotonHits DESTINATION bin)
  install(TARGETS readCalorimeterHits DESTINATION bin)
  install(TARGETS readDRCalorimeterHits DESTINATION bin)
  install(TARGETS readMscHits DESTINATION bin)
  install(FILES ${PROJECT_BINARY_DIR}/CaTSClasses_rdict.pcm DESTINATION bin)
endif()
