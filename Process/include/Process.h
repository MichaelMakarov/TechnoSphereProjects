#pragma once

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>

class Process
{
public:
	explicit Process(const std::string& path);
	~Process();

	size_t write(const void* pData, size_t length);
	void writeExact(const void* pData, size_t length);
	size_t read(void* pData, size_t length);
	void readExact(void* pData, size_t length);

	void closeStdin();

	void close();

private:
	int m_forwPipeFileDesc[2];
	int m_backPipeFileDesc[2];
	pid_t m_thisPid;
	pid_t m_childPid;
	bool m_isClosed[4];
};
