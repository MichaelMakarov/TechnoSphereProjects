#pragma once

#include <sys/types.h>
#include <sys/wait.h>
#include "FileDesc.h"
#include <string>

class Process
{
public:
	explicit Process(const std::string& path);
	~Process();
	Process(const Process& p) {}

	Process operator = (const Process& p) { return *this; }

	size_t write(const void* pData, size_t length);
	void writeExact(const void* pData, size_t length);
	size_t read(void* pData, size_t length);
	void readExact(void* pData, size_t length);

	void closeStdin();

	void close();

private:
	FileDesc m_fdForward;
	FileDesc m_fdBackward;
	pid_t m_thisPid;
	pid_t m_childPid;
};
