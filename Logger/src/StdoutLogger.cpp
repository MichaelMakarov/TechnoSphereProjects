#include "../include/StdoutLogger.h"

namespace log
{
    StdoutLogger::~StdoutLogger() {}

    void StdoutLogger::Out(const std::string& str) const
    {
        std::cout << str << std::endl;
    }

    void StdoutLogger::Flush() const {}

    void InitWithStdoutLogger(const LogLevel level)
    {
        gl_pLogger = std::make_unique<StdoutLogger>(level);
    }
}