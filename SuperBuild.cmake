#-----------------------------------------------------------------------------
# Enable and setup External project global properties
#-----------------------------------------------------------------------------
include(ExternalProject)
set(ep_base        "${CMAKE_BINARY_DIR}")

# Compute -G arg for configuring external projects with the same CMake generator:
if(CMAKE_EXTRA_GENERATOR)
  set(gen "${CMAKE_EXTRA_GENERATOR} - ${CMAKE_GENERATOR}")
else()
  set(gen "${CMAKE_GENERATOR}")
endif()

#-----------------------------------------------------------------------------
# Build options
#-----------------------------------------------------------------------------

OPTION(SLICERRT_ENABLE_EXPERIMENTAL_MODULES "Enable the building of work-in-progress, experimental modules." OFF)

#-----------------------------------------------------------------------------
# Project dependencies
#-----------------------------------------------------------------------------

set(inner_DEPENDENCIES "Plastimatch")

SlicerMacroCheckExternalProjectDependency(inner)

set(ep_cmake_args)
foreach(dep ${EXTENSION_DEPENDS})
  list(APPEND ep_cmake_args -D${dep}_DIR:PATH=${${dep}_DIR})
#  message("--------------dep:${dep}")
endforeach()

set(proj inner)

ExternalProject_Add(${proj}
  DOWNLOAD_COMMAND ""
  INSTALL_COMMAND ""
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
  BINARY_DIR ${EXTENSION_BUILD_SUBDIRECTORY}
  CMAKE_GENERATOR ${gen}
  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY:PATH=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    -DCMAKE_LIBRARY_OUTPUT_DIRECTORY:PATH=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY:PATH=${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
    -DCMAKE_CXX_COMPILER:STRING=${CMAKE_CXX_COMPILER}
    -DCMAKE_OSX_DEPLOYMENT_TARGET:STRING=${CMAKE_OSX_DEPLOYMENT_TARGET}
    -DCMAKE_OSX_SYSROOT:PATH=${CMAKE_OSX_SYSROOT}
    -DADDITIONAL_C_FLAGS:STRING=${ADDITIONAL_C_FLAGS}
    -DADDITIONAL_CXX_FLAGS:STRING=${ADDITIONAL_CXX_FLAGS}
    -D${EXTENSION_NAME}_SUPERBUILD:BOOL=OFF
    -DEXTENSION_SUPERBUILD_BINARY_DIR:PATH=${${EXTENSION_NAME}_BINARY_DIR}
    -DSLICERRT_ENABLE_EXPERIMENTAL_MODULES:BOOL=${SLICERRT_ENABLE_EXPERIMENTAL_MODULES}
    -DPlastimatch_DIR:PATH=${SLICERRT_PLASTIMATCH_DIR}
    # Slicer
    -DSlicer_DIR:PATH=${Slicer_DIR}
    -DMIDAS_PACKAGE_EMAIL:STRING=${MIDAS_PACKAGE_EMAIL}
    -DMIDAS_PACKAGE_API_KEY:STRING=${MIDAS_PACKAGE_API_KEY}
    -DSubversion_SVN_EXECUTABLE:STRING=${Subversion_SVN_EXECUTABLE}
    -DGIT_EXECUTABLE:STRING=${GIT_EXECUTABLE}
    ${ep_cmake_args}
  DEPENDS
    ${${proj}_DEPENDENCIES}
  )

# This custom external project step forces the build and later
# steps to run whenever a top level build is done...
#
# BUILD_ALWAYS flag is available in CMake 3.1 that allows force build
# of external projects without this workaround. Remove this workaround
# and use the CMake flag instead, when Slicer's required minimum CMake
# version will be at least 3.1.
#
if(CMAKE_CONFIGURATION_TYPES)
  set(BUILD_STAMP_FILE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj}-stamp/${CMAKE_CFG_INTDIR}/${proj}-build")
else()
  set(BUILD_STAMP_FILE "${CMAKE_CURRENT_BINARY_DIR}/${proj}-prefix/src/${proj}-stamp/${proj}-build")
endif()
ExternalProject_Add_Step(${proj} forcebuild
  COMMAND ${CMAKE_COMMAND} -E remove ${BUILD_STAMP_FILE}
  COMMENT "Forcing build step for '${proj}'"
  DEPENDEES build
  ALWAYS 1
  )
