#include "config_handler.hpp"

int main() {
    config::config_handler handler;

    std::optional<void*> config_opt = config::config_handler().get_config(config::app_configs::APP_ONE_CONFIG);
    return 0;
}
