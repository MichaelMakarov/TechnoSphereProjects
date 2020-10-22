#include "FileDesc.h"
#include "unistd.h"
#include <stdexcept>

FileDesc::FileDesc()
{
    int pipes[2];
    if (pipe(pipes) == -1)
        throw std::runtime_error("Failed to create pipes!");
    _pipeRead = pipes[0];
    _pipeWrite = pipes[1];
}

FileDesc::~FileDesc()
{
    Close();
}

void FileDesc::ClosePipe(int& pipe)
{
    if (pipe != -1)
    {
        close(pipe);
        pipe = -1;
    }
}

void FileDesc::Close()
{
    CloseReadPipe();
    CloseWritePipe();
}

void FileDesc::CloseReadPipe()
{
    ClosePipe(_pipeRead);
}

void FileDesc::CloseWritePipe()
{
    ClosePipe(_pipeWrite);
}

int FileDesc::GetReadPipe()
{
    return _pipeRead;
}

int FileDesc::GetWritePipe()
{
    return _pipeWrite;
}