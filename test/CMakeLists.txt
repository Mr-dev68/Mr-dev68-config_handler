cmake_minimum_required(VERSION 3.10)

project(ConfigHandlerTest)
find_package(nlohmann_json_schema_validator REQUIRED)
set(CMAKE_PREFIX_PATH "../install")

find_package(ConfigHandler REQUIRED)

add_executable(test_config_handler test.cpp)

target_link_libraries(test_config_handler ConfigHandler nlohmann_json_schema_validator)

target_include_directories(test_config_handler PRIVATE ../install/include)
