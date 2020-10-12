#pragma once
#include "BaseLogger.h"
#include <iostream>

namespace log
{
    class StderrLogger : public BaseLogger
    {
        private:
        void Out(const std::string& str) const override;
        
        public:
        using BaseLogger::BaseLogger;
        StderrLogger(const StderrLogger& logger) = delete;
        ~StderrLogger();

        StderrLogger& operator = (const StderrLogger& logger) = delete;

        void Flush() const override;
    };

    void InitWithStderrLogger(const LogLevel level);
}