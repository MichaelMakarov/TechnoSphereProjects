#include "../include/StderrLogger.h"

namespace log
{
    StderrLogger::~StderrLogger() {}

    void StderrLogger::Out(const std::string& str) const 
    {
        std::cerr << str << std::endl;
    }

    void StderrLogger::Flush() const {}

    bool InitWithStderrLogger(const LogLevel level)
    {
        if (!gl_pLogger)
        {
            gl_pLogger = std::make_unique<StderrLogger>(level);
            return true;
        }
        return false;
    }
}