#include "Logger.h"

#include <chrono>

std::string XERN_LOGGER::Logger::GetCurrentDateTime() {
    auto now = std::chrono::system_clock::now();
    return std::format("[{:%Y.%m.%d-%H:%M}]", now);
}
