cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Simula)

# Set the C++ standard (if needed)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(VTK COMPONENTS 
  CommonColor
  CommonCore
  CommonDataModel
  IOLegacy
  InteractionStyle
  RenderingContextOpenGL2
  RenderingCore
  RenderingFreeType
  RenderingGL2PSOpenGL2
  RenderingOpenGL2
  RenderingVolume
  RenderingVolumeOpenGL2
  FiltersSources
  FiltersCore
  FiltersGeometry
  FiltersGeneral
  FiltersModeling
  IOImage
  REQUIRED
)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "SimpleRayCast: Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")

# Find the SFML package
find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

add_subdirectory(src)