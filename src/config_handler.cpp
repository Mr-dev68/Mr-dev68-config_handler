#include "config_handler.hpp"
#include "config_structures.hpp"
#include "default_configs.hpp"
#include "generated/app_one_config.hpp"
#include "generated/app_two_config.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <nlohmann/json-schema.hpp>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
namespace config {

using nlohmann::json;
using nlohmann::json_schema::json_validator;
config_handler::~config_handler() {}
config_handler::config_handler(){};
bool inline parse_json_from_file(const std::string& file_path, json& j) {
    std::ifstream input(file_path);
    try {

        if (input.is_open()) {
            input >> j;
            input.close();
            return true;
        } else {
            printf("file is not open %s \n", file_path.c_str());
            return false;
        }

    } catch (const std::exception& e) {
        printf("can not parse the json config: %s using default \n ", e.what());
    }
    return false;
}

std::optional<void*> config_handler::get_config(const app_configs in, bool with_validation) {
    printf(" getting config from %s\n", json_paths.at(in));
    json data_json;
    bool use_default(false);
    const char* path = std::getenv(env_config_path);
    if ((path) && (parse_json_from_file(path, data_json))) {
        printf(" getting configs from env %s \n", path);
    } else if (!parse_json_from_file(std::string(json_paths.at(in)), data_json)) {
        use_default = true;
    }

    if (in == app_configs::APP_ONE_CONFIG) {
        app_one_config::AppOneConfig config_interface;
        if (use_default || data_json.is_null()) {
            printf("using default APP_ONE_CONFIG %d %s\n", data_json.is_null(), data_json.dump().c_str());
            data_json = nlohmann::json::parse(config::app_one_config_default);
        } else {
            try {
                if (with_validation) {
                    if (!validate_json_string(app_configs::APP_ONE_CONFIG, data_json.dump()))
                        return std::nullopt;
                }
                app_one_config::from_json(data_json, config_interface);
            } catch (const std::exception& e) {
                printf("cant use the config, using LIFECYC_MANAGER_CONFIG default "
                       "error: %s\n",
                       e.what());
                data_json = nlohmann::json::parse(config::app_one_config_default);
            }
        };
        app_one_config::from_json(data_json, config_interface);
        printf(" configuration used : \n %s \n", data_json.dump().c_str());
        return new app_one_config_str(config_interface.get_m_cpr1(), config_interface.get_m_cpr2(), config_interface.get_m_object().get_op1(),
                                      config_interface.get_m_object().get_op2());
    } else if (in == app_configs::APP_TWO_CONFIG) {

        app_two_config::AppTwoConfig config_interface;
        if (use_default || data_json.is_null()) {
            printf("using default APP_TWO_CONFIG %d %s\n", data_json.is_null(), data_json.dump().c_str());
            data_json = nlohmann::json::parse(config::app_two_config_default);
        } else {
            try {
                if (with_validation) {
                    if (!validate_json_string(app_configs::APP_ONE_CONFIG, data_json.dump()))
                        return std::nullopt;
                }
                app_two_config::from_json(data_json, config_interface);
            } catch (const std::exception& e) {
                printf("cant use the config, using APP_TWO_CONFIG default "
                       "error: %s\n",
                       e.what());
                data_json = nlohmann::json::parse(config::app_one_config_default);
            }
        };
        app_two_config::from_json(data_json, config_interface);
        printf(" configuration used : \n %s \n", data_json.dump().c_str());
        return new app_two_config_str(config_interface.get_m_cpr1(), config_interface.get_m_cpr2());
    }
    return std::nullopt;
}

bool config_handler::validate_json_string(const app_configs app_id, const std::string& json_string) {

    json schema;
    try {
        if (!parse_json_from_file(std::string(schema_paths.at(app_id)), schema)) {
            printf(" can nost parse schema for app %d \n", static_cast<uint8_t>(app_id));
            return false;
        }
    } catch (const std::exception& e) {
        printf(" can nost parse schema for app %d crashed %s\n", static_cast<uint8_t>(app_id), e.what());
        return false;
    }

    try {
        json parsed_json = json::parse(json_string);

        // Create a JSON schema validator
        json_validator validator;

        // Set the schema for the validator
        validator.set_root_schema(schema);
        validator.validate(parsed_json);

        printf(" validation successfull \n");
        return true;

    } catch (const std::exception& e) {
        printf("  validation failed why: %s\n", e.what());
        return false;
    }
};

bool config_handler::validate_json_string(const char* json_str, const char* json_schema_str, std::string& err) {
    err.clear();

    try {
        json parsed_json = json::parse(json_str);
        json schema = json::parse(json_schema_str);
        // Create a JSON schema validator
        json_validator validator;

        // Set the schema for the validator
        validator.set_root_schema(schema);
        validator.validate(parsed_json);
        return true;

    } catch (const std::exception& e) {
        printf("  validation failed why: %s\n", e.what());
        err = "validation failed why:" + std::string(e.what());
        return false;
    }
};
} // namespace config
