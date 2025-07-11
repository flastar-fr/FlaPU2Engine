#pragma once

enum class EngineRunningStatus {
    RUNNING,
    PAUSED,
    STOPPED
};

struct EngineStatus {
    EngineStatus(): op_per_second(10), running_status(EngineRunningStatus::RUNNING), instruction_accumulator(0.0f) {};

    int op_per_second;
    EngineRunningStatus running_status;
    float instruction_accumulator;
};
