﻿#include "../include/Process.h"
#include <stdexcept>


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
	size_t len;
	do {
		len = write(pData, length);
	} while (len != length);
}

size_t Process::read(void* pData, size_t length)
{
	return ::read(m_fdBackward.GetReadPipe(), pData, length);
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
	m_fdForward.Close();
}

void Process::close()
{
	if (m_fdForward.IsClosed())
		m_fdForward.Close();
	if (m_fdBackward.IsClosed())
		m_fdBackward.Close();
}