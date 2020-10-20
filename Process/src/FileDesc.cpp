#include "../include/FileDesc.h"
#include <stdexcept>

FileDesc::FileDesc()
{
    if (pipe(m_pipes) == -1)
        throw std::runtime_error("Failed to create pipes!");
    m_isClosed = false;
}

FileDesc::~FileDesc()
{
    Close();
}

void FileDesc::Close()
{
    if (!m_isClosed)
    {
        close(m_pipes[0]);
        close(m_pipes[1]);
        m_isClosed =  true;
    }
}

const int FileDesc::GetReadPipe()
{
    return m_pipes[PIPE_READ];
}

const int FileDesc::GetWritePipe()
{
    return m_pipes[PIPE_WRITE];
}

bool FileDesc::IsClosed()
{
    return m_isClosed;
}