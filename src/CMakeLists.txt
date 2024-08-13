# Automatically gather all .cpp files in the current directory
file(GLOB SOURCES "*.cpp")

# Add the executable using all .cpp files found
add_executable(main MACOSX_BUNDLE ${SOURCES})

# Link SFML libraries
target_link_libraries(main sfml-graphics sfml-window sfml-system)

# Link VTK libraries
target_link_libraries(main ${VTK_LIBRARIES})
