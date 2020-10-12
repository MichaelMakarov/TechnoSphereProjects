#include "../include/FileLogger.h"
#include <vector>

namespace log
{
    std::vector<std::ofstream> fouts;
    
    FileLogger::FileLogger(const LogLevel level, const std::string& filePath) : BaseLogger(level)
    {
        fouts.push_back(std::ofstream(filePath, std::ios_base::out));
        if (!fouts.back()) 
            throw std::runtime_error("Failed to open log file!");
        m_index = fouts.size() - 1;
    }

    FileLogger::~FileLogger() 
    { 
        Flush();
        fouts[m_index].close(); 
    }

    void FileLogger::Out(const std::string& str) const
    {
        fouts[m_index] << str << "\n";
    }

    void FileLogger::Flush() const
    {
        fouts[m_index].flush();
    }

    void InitWithFileLogger(const LogLevel level, const std::string& filePath)
    {
        gl_pLogger = std::make_unique<FileLogger>(level, filePath);
    }
}