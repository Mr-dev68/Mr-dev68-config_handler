#ifndef CONFIG_HANDLER_HPP
#define CONFIG_HANDLER_HPP
#pragma once

#include "config_structures.hpp"
#include <iostream>
#include <optional>

namespace config {
static const char* env_config_path = "F_CONFIG";
class config_handler {
  public:
    config_handler();
    virtual ~config_handler();
    std::optional<void*> get_config(const app_configs in, bool with_validation = false);
    bool validate_json_string(const app_configs app_id, const std::string& json_string);
    bool validate_json_string(const char* json_str, const char* json_schema_str, std::string& err);
};
} // namespace config

#endif