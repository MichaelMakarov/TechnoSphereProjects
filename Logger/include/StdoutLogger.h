#pragma once
#include "BaseLogger.h"
#include <iostream>

namespace log
{
    class StdoutLogger : public BaseLogger
    {
        private:
        void Out(const std::string& str) const override;

        public:
        using BaseLogger::BaseLogger;
        StdoutLogger(const StdoutLogger& logger) = delete;
        ~StdoutLogger();

        StdoutLogger& operator = (const StdoutLogger& logger) = delete;

        void Flush() const override;
    };

    bool InitWithStdoutLogger(const LogLevel level);
}