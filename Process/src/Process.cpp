#include "../include/Process.h"
#include <iostream>
#include <exception>

#define PIPE_READ 0
#define PIPE_WRITE 1

Process::Process(const std::string& path)
{
	if (pipe(m_forwPipeFileDesc) == -1 ||
		pipe(m_backPipeFileDesc) == -1)
		throw std::runtime_error("Failed to create forward and backward pipes!");
	for (size_t i = 0; i < 4; ++i)
		m_isClosed[i] = false;
	m_thisPid = getpid();
	m_childPid = fork();
	if (m_childPid < 0)
		throw std::runtime_error("Failed to create a process!");
	else if (m_childPid == 0)
	{
		std::cout << "Child process successfully created!\n";
		std::cout << "Child pid = " << getpid() << ", parent pid = " << getppid() << std::endl;
		
		if (dup2(m_forwPipeFileDesc[PIPE_READ], STDIN_FILENO) == -1)
			throw std::runtime_error("Failed to create stdin!");
		if (dup2(m_backPipeFileDesc[PIPE_WRITE], STDOUT_FILENO) == -1)
			throw std::runtime_error("Failed to create stdout!");
		if (execl(path.c_str(), nullptr) == -1)
		{
			std::string errorMsg = "Failed to execute the program: " + path;
			throw std::runtime_error(errorMsg.c_str());
		}
	}
}

Process::~Process()
{
	close();
}

size_t Process::write(const void* pData, size_t length)
{
	return ::write(m_forwPipeFileDesc[PIPE_WRITE], pData, length);
}

void Process::writeExact(const void* pData, size_t length)
{
	size_t len;
	do {
		len = write(pData, length);
	} while (len != length);
}

size_t Process::read(void* pData, size_t length)
{
	return ::read(m_backPipeFileDesc[PIPE_READ], pData, length);
}

void Process::readExact(void* pData, size_t length)
{
	size_t len = 0;
	do {
		len += read(pData, length);
	} while (len != length);
}

void Process::closeStdin()
{
	::close(m_forwPipeFileDesc[PIPE_WRITE]);
	::close(m_forwPipeFileDesc[PIPE_READ]);
	m_isClosed[0] = m_isClosed[1] = true;
}

void Process::close()
{
	if (!m_isClosed[0])
		closeStdin();
	if (!m_isClosed[2])
	{
		::close(m_backPipeFileDesc[PIPE_WRITE]);
		::close(m_backPipeFileDesc[PIPE_READ]);
		m_isClosed[2] = m_isClosed[3] = true;
}