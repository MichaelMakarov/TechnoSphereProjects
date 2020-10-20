#pragma once
#include <string>
#include <memory>

namespace log
{
    enum LogLevel
    {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    class BaseLogger
    {
        protected:
        LogLevel m_level;

        bool CheckLevel(const LogLevel& level) const;

        virtual void Out(const std::string& str) const = 0;

        public:
        BaseLogger(const LogLevel level);
        BaseLogger(const BaseLogger& logger) = delete;
        ~BaseLogger();

        BaseLogger& operator = (const BaseLogger& logger) = delete;

        void Debug(const std::string& str) const;
        void Info(const std::string& str) const;
        void Warn(const std::string& str) const;
        void Error(const std::string& str) const;

        void SetLevel(const LogLevel level);
        const LogLevel Level() const;

        virtual void Flush() const = 0;
    };

    extern std::unique_ptr<BaseLogger> gl_pLogger;

    void Debug(const std::string& str);
    void Info(const std::string& str);
    void Warn(const std::string& str);
    void Error(const std::string& str);
}
