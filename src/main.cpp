#include "main_components/pre_data_extraction.hpp"
#include "config/config_file_management.hpp"
#include "config/main_config.hpp"
#include "gui/gui_handling.hpp"

void start_engine() {
    auto json_file = open_config_file(JSON_CONFIG_PATH);

    const auto instructions = get_instructions(json_file[SOURCE_PATH_KEY]);

    auto engine_runner = EngineRunner(Engine(), instructions, json_file[CLOCK_SPEED_KEY], json_file[SOURCE_PATH_KEY], json_file[SHOW_DEBUG_KEY]);
    create_window(engine_runner, json_file);

    save_config_file(JSON_CONFIG_PATH, engine_runner.getEngineStatus(), json_file);
}

int main() {
    start_engine();

    return 0;
}
