#pragma once
#include "unistd.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

class FileDesc
{
    private:
    int m_pipes[2];
    bool m_isClosed;

    public:
    FileDesc();
    FileDesc(const FileDesc& fd) {}
    ~FileDesc();

    FileDesc& operator = (const FileDesc& fd) { return *this; }

    void Close();

    const int GetReadPipe();
    const int GetWritePipe();

    bool IsClosed();
};