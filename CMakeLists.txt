cmake_minimum_required(VERSION 3.9)

# Set the project name
project(main)
set(MAIN_SOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-14)
# set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-14)
# Set Clang as the compiler
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ENV{PATH} "/usr/local/opt/llvm/bin:$ENV{PATH}")
set(OpenMP_C_FLAGS "-fopenmp")
set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_CXX_FLAGS "-fopenmp")
set(OpenMP_CXX_LIB_NAMES "omp")

set(OpenMP_omp_LIBRARY /opt/homebrew/Cellar/libomp/18.1.8/lib/libomp.dylib)

# Find Eigen
find_package(Eigen3 3.4 REQUIRED)
# Find OpenMP
find_package(OpenMP REQUIRED)

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


if(APPLE)
    message(STATUS "Checking if OpenMP there!")
    find_package(OpenMP REQUIRED)
    if(OpenMP_CXX_FOUND)
        message(STATUS "Adding compile options!")
        add_compile_options(-Xpreprocessor -fopenmp)
        # Specify the library path
        set(OpenMP_LIB_PATH /opt/homebrew/Cellar/libomp/18.1.8/lib/)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${OpenMP_LIB_PATH} -lomp")
    endif()
else()
    find_package(OpenMP REQUIRED)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${PROJECT_NAME} OpenMP::OpenMP_CXX)
    endif()
endif()

add_subdirectory(src)