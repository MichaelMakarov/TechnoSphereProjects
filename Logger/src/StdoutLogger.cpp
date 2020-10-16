#include "../include/StdoutLogger.h"

namespace log
{
    StdoutLogger::~StdoutLogger() {}

    void StdoutLogger::Out(const std::string& str) const
    {
        std::cout << str << std::endl;
    }

    void StdoutLogger::Flush() const {}

    bool InitWithStdoutLogger(const LogLevel level)
    {
        if (!gl_pLogger)
        {
            gl_pLogger = std::make_unique<StdoutLogger>(level);
            return true;
        }
        return false;
    }
}