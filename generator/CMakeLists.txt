cmake_minimum_required(VERSION 3.10)

project(Config_generator)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Check if Quicktype is available
find_program(QUICKTYPE_EXECUTABLE quicktype)
if(NOT QUICKTYPE_EXECUTABLE)
    message(FATAL_ERROR "quicktype executable not found. Please install quicktype.")
endif()

# Output directory for generated files
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated)

# Create the generated directory if it does not exist
file(MAKE_DIRECTORY ${GENERATED_DIR})

# Find all JSON schema files in the schemas directory
file(GLOB JSON_SCHEMAS ${CMAKE_CURRENT_SOURCE_DIR}/schemas/*.json)

# Initialize lists to hold generated header files
set(GENERATED_HEADERS)

# Add custom command to run Quicktype on each schema to generate only headers
foreach(SCHEMA ${JSON_SCHEMAS})
    get_filename_component(SCHEMA_NAME ${SCHEMA} NAME_WE)

    # Remove "Config" or "Data" suffix from the schema name to create the namespace
    string(REGEX REPLACE "(Config|Data)$" "" NAMESPACE_NAME ${SCHEMA_NAME})

    set(GENERATED_HEADER ${GENERATED_DIR}/${SCHEMA_NAME}.hpp)
    
    add_custom_command(
        OUTPUT ${GENERATED_HEADER}
        COMMAND quicktype --lang cpp --src-lang schema --include-location global-include --no-boost --out ${GENERATED_HEADER} --src ${SCHEMA} --namespace "config::${NAMESPACE_NAME}"
        DEPENDS ${SCHEMA}
        COMMENT "Running quicktype on ${SCHEMA} with namespace ${NAMESPACE_NAME}"
        VERBATIM
    )
    list(APPEND GENERATED_HEADERS ${GENERATED_HEADER})
endforeach()




# Add a custom target to group all generated files
add_custom_target(${PROJECT_NAME} ALL DEPENDS ${GENERATED_HEADERS})
