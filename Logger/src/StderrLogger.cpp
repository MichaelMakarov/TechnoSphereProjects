#include "../include/StderrLogger.h"

namespace log
{
    StderrLogger::~StderrLogger() {}

    void StderrLogger::Out(const std::string& str) const 
    {
        std::cerr << str << std::endl;
    }

    void StderrLogger::Flush() const {}

    void InitWithStderrLogger(const LogLevel level)
    {
        gl_pLogger = std::make_unique<StderrLogger>(level);
    }
}