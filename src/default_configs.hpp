#ifndef DEFAULT_CONFIGS_HPP
#define DEFAULT_CONFIGS_HPP

#pragma once
#include <string>

namespace config {

static const std::string app_one_config_default = R"({
    "m_cpr1": 1000,
    "m_cpr2": 5,
    "m_object": {
        "op1": 1,
        "op2": 10
    }
})";

static const std::string app_two_config_default = R"({
    "m_cpr1": "test",
    "m_cpr2": 5,
})";
} // namespace config
#endif