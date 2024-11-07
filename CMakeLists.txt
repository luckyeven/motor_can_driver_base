cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the paths for the source and header files
set(SOURCE_FILES
    Example/main.cpp
    Robot/actuators/ctrl_motor.cpp
    Robot/instances/singlemotor.cpp
    Bridge/interface_can.cpp
    Utils/src/can.cpp
)

set(HEADER_FILES
    Bridge/interface_can.hpp
    Robot/actuators/ctrl_motor.hpp
    Robot/instances/singlemotor.h
    Utils/cancontrol/include/can.hpp
    Utils/cancontrol/controlcan.h
)

# Include the header directories
include_directories(
    Bridge
    Robot/actuators
    Robot/instances
    Utils/cancontrol/include
)

# Add the executable target
add_executable(MyExecutable ${SOURCE_FILES} ${HEADER_FILES})

# Link the shared library `libcontrolcan.so`
target_link_libraries(MyExecutable PRIVATE
    Utils/cancontrol/libcontrolcan.so
)

# Optionally set the output directory for the executable
set_target_properties(MyExecutable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

