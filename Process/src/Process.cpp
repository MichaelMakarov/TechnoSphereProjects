#include "../include/Process.h"
#include <stdexcept>
#include <memory>


Process::Process(const std::string& path)
{
	m_thisPid = getpid();
	m_childPid = fork();
	if (m_childPid < 0)
		throw std::runtime_error("Failed to create a process!");
	else if (m_childPid == 0)
	{
		if (dup2(m_fdForward.GetReadPipe(), STDIN_FILENO) == -1)
			throw std::runtime_error("Failed to create stdin!");
		if (dup2(m_fdBackward.GetWritePipe(), STDOUT_FILENO) == -1)
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
	return ::write(m_fdForward.GetWritePipe(), pData, length);
}

void Process::writeExact(const void* pData, size_t length)
{
	size_t len = 0;
	const char* pStr = static_cast<const char*>(pData);
	do {
		len += write(&(pStr[len]), length - len);
	} while (len < length - 1);
}

size_t Process::read(void* pData, size_t length)
{
	return ::read(m_fdBackward.GetReadPipe(), pData, length);
}

void Process::readExact(void* pData, size_t length)
{
	size_t len = 0, cur;
	char* pStr = static_cast<char*>(pData);
	std::unique_ptr<char[]> pBuf {new char[length]};
	do {
		cur = read(pBuf.get(), length);
		for (size_t i = 0; i < cur && len < length; ++i, ++len)
			pStr[len] = pBuf[i];
	} while (len < length);
}

void Process::closeStdin()
{
	m_fdForward.Close();
}

void Process::close()
{
	if (!m_fdForward.IsClosed())
		m_fdForward.Close();
	if (!m_fdBackward.IsClosed())
		m_fdBackward.Close();
}