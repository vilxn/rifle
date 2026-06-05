#ifndef XERN2D_LOGGER_H
#define XERN2D_LOGGER_H
#include <format>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#define XERN_INFO(x, ...) XERN_LOGGER::Logger::GetInstance().INFO(x, ##__VA_ARGS__);

namespace XERN_LOGGER{
struct LoggerEntry {
    enum class LogType {
        INFO, ERROR, WARNING
    };

    LogType type;
    std::string log{};
};

class Logger {
private:
    std::string GetCurrentDateTime();
    std::list<LoggerEntry> m_entries{};
    Logger() = default;

public:
    static Logger& GetInstance() {
        static Logger instance;
        return instance;
    }

    template<typename ...Args>
    void INFO(const std::string_view message, Args&& ...args) {
        LoggerEntry entry;
        entry.type = LoggerEntry::LogType::INFO;
        std::stringstream ss;
        ss << "Xern2D "
           << "[INFO] "
           << GetCurrentDateTime()
           << ": ";
        ss << std::vformat(message, std::make_format_args(std::forward<Args>(args)...)) << "\n";
        entry.log = ss.str();

        m_entries.push_back(entry);
        std::cout << entry.log;
    }

    ~Logger() = default;

    Logger (const Logger&) = delete;
    Logger& operator= (const Logger&) = delete;
};
}


#endif //XERN2D_LOGGER_H
