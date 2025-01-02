#ifndef CONFIG_STRUCTURES_HPP
#define CONFIG_STRUCTURES_HPP

#pragma once
#include <map>
#include <string>
#include <vector>

namespace config {

enum class app_configs : uint8_t { APP_ONE_CONFIG = 0, APP_TWO_CONFIG, ALL };

static const std::map<app_configs, const char*> json_paths{{app_configs::APP_ONE_CONFIG, "app_one_config.json"},
                                                           {app_configs::APP_TWO_CONFIG, "app_two_config.json"}};

static const std::map<app_configs, const char*> schema_paths{{app_configs::APP_ONE_CONFIG, "app_one_config_schema.json"},
                                                             {app_configs::APP_TWO_CONFIG, "app_two_config_schema.json"}};

struct app_one_config_str {
    app_one_config_str() = delete;
    app_one_config_str(int16_t cpr1, int16_t cpr2, int16_t ob_cp1, int16_t ob_cp2) : m_cpr1(cpr1), m_cpr2(cpr2), m_ob_cp1(ob_cp1), m_ob_cp2(ob_cp2){};
    int16_t m_cpr1;
    int16_t m_cpr2;
    int16_t m_ob_cp1;
    int16_t m_ob_cp2;
};

struct app_two_config_str {
    app_two_config_str() = delete;
    app_two_config_str(std::string cpr1, int16_t cpr2) : m_cpr1(cpr1), m_cpr2(cpr2){};
    std::string m_cpr1;
    int16_t m_cpr2;
};

} // namespace config

#endif