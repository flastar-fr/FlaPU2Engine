#pragma once

enum class EngineRunningStatus {
    RUNNING,
    PAUSED,
    STOPPED
};

struct EngineStatus {
    EngineStatus(): opPerSecond(10), runningStatus(EngineRunningStatus::RUNNING) {}

    int opPerSecond;
    EngineRunningStatus runningStatus;
};
