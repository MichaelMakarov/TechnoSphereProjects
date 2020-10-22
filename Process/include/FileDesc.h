#pragma once

class FileDesc
{
    private:
    int _pipeRead;
    int _pipeWrite;

    void ClosePipe(int& pipe);

    public:
    FileDesc();
    FileDesc(const FileDesc& fd) = delete;
    ~FileDesc();

    FileDesc& operator = (const FileDesc& fd) = delete;

    void Close();

    int GetReadPipe();
    int GetWritePipe();

    void CloseReadPipe();
    void CloseWritePipe();
};