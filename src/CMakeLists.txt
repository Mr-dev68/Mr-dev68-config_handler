project(ConfigHandler)

cmake_minimum_required(VERSION 3.10)
add_compile_options(-Wall -Wextra -Wpedantic -march=native)
find_package(nlohmann_json_schema_validator REQUIRED)
if(nlohmann_json_schema_validator_FOUND)
    message(STATUS "nlohmann_json_schema_validator found successfully.")
else()
    message(FATAL_ERROR "nlohmann_json_schema_validator not found. Please make sure it is installed and accessible.")
endif()

option(BUILD_SHARED_LIBS "Build as a shared library" ON)

# Add the library target
add_library(${PROJECT_NAME}
    config_handler.cpp
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # For config_structure.hpp and config_handler.hpp
        $<BUILD_INTERFACE:"${CMAKE_SOURCE_DIR}/generator">
        $<INSTALL_INTERFACE:include>                    # For installation targets
    PRIVATE   
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  # For config_structure.hpp and config_handler.hpp
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/generator> 
)


message(WARNING "nlohmann_json_schema_validator must be linked by the consuming project when using ConfigHandlerLibrary.")

# Optional: Install the library and headers
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install public headers
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/config_structures.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/config_handler.hpp"
    DESTINATION include
)

# Install the export set for use with find_package
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
)

