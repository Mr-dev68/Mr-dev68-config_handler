//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     AppOneConfig data = nlohmann::json::parse(jsonString);

#pragma once

#include <nlohmann/json.hpp>

#include <optional>
#include <stdexcept>
#include <regex>

namespace config {
namespace app_one_config {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_config_app_one_config_HELPER
    #define NLOHMANN_UNTYPED_config_app_one_config_HELPER
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

    class MObject {
        public:
        MObject() = default;
        virtual ~MObject() = default;

        private:
        int64_t op1;
        int64_t op2;

        public:
        /**
         * test  variable
         */
        const int64_t & get_op1() const { return op1; }
        int64_t & get_mutable_op1() { return op1; }
        void set_op1(const int64_t & value) { this->op1 = value; }

        /**
         * test  variable
         */
        const int64_t & get_op2() const { return op2; }
        int64_t & get_mutable_op2() { return op2; }
        void set_op2(const int64_t & value) { this->op2 = value; }
    };

    class AppOneConfig {
        public:
        AppOneConfig() = default;
        virtual ~AppOneConfig() = default;

        private:
        int64_t m_cpr1;
        int64_t m_cpr2;
        MObject m_object;

        public:
        /**
         * test variable
         */
        const int64_t & get_m_cpr1() const { return m_cpr1; }
        int64_t & get_mutable_m_cpr1() { return m_cpr1; }
        void set_m_cpr1(const int64_t & value) { this->m_cpr1 = value; }

        /**
         * test variable
         */
        const int64_t & get_m_cpr2() const { return m_cpr2; }
        int64_t & get_mutable_m_cpr2() { return m_cpr2; }
        void set_m_cpr2(const int64_t & value) { this->m_cpr2 = value; }

        const MObject & get_m_object() const { return m_object; }
        MObject & get_mutable_m_object() { return m_object; }
        void set_m_object(const MObject & value) { this->m_object = value; }
    };
}
}

namespace config {
namespace app_one_config {
    void from_json(const json & j, MObject & x);
    void to_json(json & j, const MObject & x);

    void from_json(const json & j, AppOneConfig & x);
    void to_json(json & j, const AppOneConfig & x);

    inline void from_json(const json & j, MObject& x) {
        x.set_op1(j.at("op1").get<int64_t>());
        x.set_op2(j.at("op2").get<int64_t>());
    }

    inline void to_json(json & j, const MObject & x) {
        j = json::object();
        j["op1"] = x.get_op1();
        j["op2"] = x.get_op2();
    }

    inline void from_json(const json & j, AppOneConfig& x) {
        x.set_m_cpr1(j.at("m_cpr1").get<int64_t>());
        x.set_m_cpr2(j.at("m_cpr2").get<int64_t>());
        x.set_m_object(j.at("m_object").get<MObject>());
    }

    inline void to_json(json & j, const AppOneConfig & x) {
        j = json::object();
        j["m_cpr1"] = x.get_m_cpr1();
        j["m_cpr2"] = x.get_m_cpr2();
        j["m_object"] = x.get_m_object();
    }
}
}
