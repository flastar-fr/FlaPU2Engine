#pragma once

enum class EngineRunningStatus {
    RUNNING,
    PAUSED,
    STOPPED
};

struct EngineStatus {
    EngineStatus(): op_per_second(10), running_status(EngineRunningStatus::RUNNING) {}

    int op_per_second;
    EngineRunningStatus running_status;
};
