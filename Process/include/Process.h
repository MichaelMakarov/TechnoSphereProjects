#pragma once
#include "FileDesc.h"
#include <string>

class Process
{
public:
	explicit Process(const std::string& path);
	~Process();
	Process(const Process& p) = delete;

	Process operator = (const Process& p) = delete;

	size_t write(const void* pData, size_t length);
	void writeExact(const void* pData, size_t length);
	size_t read(void* pData, size_t length);
	void readExact(void* pData, size_t length);

	void closeStdin();

	void close();

private:
	FileDesc _fdForward;
	FileDesc _fdBackward;
	pid_t _childPid;
};
