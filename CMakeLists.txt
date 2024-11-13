cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)
set(CMAKE_BUILD_TYPE Debug)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the paths for the source and header files
set(SOURCE_FILES
  


    Utils/cancontrol/src/can.cpp
    Bridge/communication/interface_can.cpp
    Robot/actuators/ctrl_motor.cpp
    Robot/instances/singlemotor.cpp
    Robot/instances/prototype_robot.cpp
    Example/main.cpp
)

set(HEADER_FILES
    Bridge/communication/interface_can.hpp
    Robot/actuators/ctrl_motor.hpp
    Robot/instances/singlemotor.h
    Robot/instances/prototype_robot.h
    Utils/cancontrol/include/can.hpp
    Utils/cancontrol/controlcan.h
       
)

# Include the header directories
include_directories(
    Bridge
    Robot/actuators
    Robot/instances
    Utils/cancontrol/include
    Utils/cancontrol
    Bridge/communication
    Robot/algorithms/kinematic
)

# Add the executable target
add_executable(${PROJECT_NAME}_bin ${SOURCE_FILES} ${HEADER_FILES})

# Link the shared library `libcontrolcan.so`

target_link_libraries(${PROJECT_NAME}_bin ${CMAKE_SOURCE_DIR}/Utils/cancontrol/libcontrolcan.so pthread
)

# Optionally set the output directory for the executable
set_target_properties(${PROJECT_NAME}_bin PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

