#pragma once

enum class EngineRunningStatus {
    RUNNING,
    PAUSED,
    STOPPED
};

struct EngineStatus {
    explicit EngineStatus(const int op_per_second, const std::string& source_path): op_per_second(op_per_second), running_status(EngineRunningStatus::RUNNING), instruction_accumulator(0.0f), current_file_path(source_path) {}

    int op_per_second;
    EngineRunningStatus running_status;
    float instruction_accumulator;
    std::string current_file_path;
};
