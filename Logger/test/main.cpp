#include "../include/FileLogger.h"
#include "../include/StdoutLogger.h"
#include "../include/StderrLogger.h"

int main()
{
    log::InitWithStdoutLogger(log::WARN);
    log::Error("This is an error for stdout logger!");
    log::Warn("This is a warning for stdout logger!");
    log::Info("This is an info message for stdout logger!");
    log::Debug("This is a debug infomation for stdout logger!");

    log::InitWithStderrLogger(log::INFO);
    log::Error("This is an error for stderr logger!");
    log::Warn("This is a warning for stderr logger!");
    log::Info("This is an info message for stderr logger!");
    log::Debug("This is a debug infomation for stderr logger!");

    log::InitWithFileLogger(log::DEBUG, "logfile.txt");
    log::Error("This is an error for file logger!");
    log::Warn("This is a warning for file logger!");
    log::Info("This is an info message for file logger!");
    log::Debug("This is a debug infomation for file logger!");

    return 0;
}