#pragma once
#include "BaseLogger.h"
#include <fstream>

namespace log
{
    class FileLogger : public BaseLogger
    {
        protected:        
        void Out(const std::string& str) const override;

        size_t m_index;

        public:
        FileLogger(const LogLevel level, const std::string& filePath);
        FileLogger(const FileLogger& logger) = delete;
        ~FileLogger();

        FileLogger& operator = (const FileLogger& logger) = delete;

        void Flush() const override;
    };

    bool InitWithFileLogger(const LogLevel level, const std::string& filePath);
}