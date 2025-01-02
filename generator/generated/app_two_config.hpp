//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     AppTwoConfig data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

#include <optional>
#include <stdexcept>
#include <regex>

namespace config {
namespace app_two_config {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_config_app_two_config_HELPER
    #define NLOHMANN_UNTYPED_config_app_two_config_HELPER
    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }
    #endif

    class AppTwoConfig {
        public:
        AppTwoConfig() = default;
        virtual ~AppTwoConfig() = default;

        private:
        std::string m_cpr1;
        int64_t m_cpr2;

        public:
        /**
         * test variable
         */
        const std::string & get_m_cpr1() const { return m_cpr1; }
        std::string & get_mutable_m_cpr1() { return m_cpr1; }
        void set_m_cpr1(const std::string & value) { this->m_cpr1 = value; }

        /**
         * test variable
         */
        const int64_t & get_m_cpr2() const { return m_cpr2; }
        int64_t & get_mutable_m_cpr2() { return m_cpr2; }
        void set_m_cpr2(const int64_t & value) { this->m_cpr2 = value; }
    };
}
}

namespace config {
namespace app_two_config {
    void from_json(const json & j, AppTwoConfig & x);
    void to_json(json & j, const AppTwoConfig & x);

    inline void from_json(const json & j, AppTwoConfig& x) {
        x.set_m_cpr1(j.at("m_cpr1").get<std::string>());
        x.set_m_cpr2(j.at("m_cpr2").get<int64_t>());
    }

    inline void to_json(json & j, const AppTwoConfig & x) {
        j = json::object();
        j["m_cpr1"] = x.get_m_cpr1();
        j["m_cpr2"] = x.get_m_cpr2();
    }
}
}
