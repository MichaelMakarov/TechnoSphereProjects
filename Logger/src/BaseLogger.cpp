#include "../include/BaseLogger.h"

namespace log
{
    BaseLogger::BaseLogger(const LogLevel level)
    {
        m_level = level;
    }

    BaseLogger::~BaseLogger() {}

    void BaseLogger::SetLevel(const LogLevel level)
    {
        m_level = level;
    }

    const LogLevel log::BaseLogger::Level() const
    {
        return m_level;
    }

    bool BaseLogger::CheckLevel(const LogLevel& level) const
    {
        return m_level <= level;
    }

    void BaseLogger::Debug(const std::string& str) const
    {
        if (CheckLevel(LogLevel::DEBUG)) Out(str);
    }

    void BaseLogger::Info(const std::string& str) const
    {
        if (CheckLevel(LogLevel::INFO)) Out(str);
    }

    void BaseLogger::Warn(const std::string& str) const
    {
        if (CheckLevel(LogLevel::WARN)) Out(str);
    }

    void BaseLogger::Error(const std::string& str) const
    {
        if (CheckLevel(LogLevel::ERROR)) Out(str);
    }

    void Debug(const std::string& str)
    {
        gl_pLogger->Debug(str);
    }

    void Info(const std::string& str)
    {
        gl_pLogger->Info(str);
    }

    void Warn(const std::string& str)
    {
        gl_pLogger->Warn(str);
    }

    void Error(const std::string& str)
    {
        gl_pLogger->Error(str);
    }

    std::unique_ptr<BaseLogger> gl_pLogger = nullptr;
}