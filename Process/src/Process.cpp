#include "Process.h"
#include <sys/wait.h>
#include <unistd.h>
#include <memory>
#include <iostream>


Process::Process(const std::string& path)
{
	_thisPid = getpid();
	if (_childPid < 0)
		throw std::runtime_error("Failed to create a process!");
	else if (_childPid == 0)
	{
		if (dup2(_fdForward.GetReadPipe(), STDIN_FILENO) == -1)
			std::exit(-1);
		if (dup2(_fdBackward.GetWritePipe(), STDOUT_FILENO) == -1)
			std::exit(-1);
		if (execl(path.c_str(), path.c_str(), nullptr) == -1)
			std::exit(-1);
	}
}

Process::~Process()
{
	close();
}

size_t Process::write(const void* pData, size_t length)
{
	ssize_t l = ::write(_fdForward.GetWritePipe(), pData, length);
	std::cout << l << "\n";
	if (l == -1)
		throw std::runtime_error("An error occured!");
	return static_cast<size_t>(l);
}

void Process::writeExact(const void* pData, size_t length)
{
	size_t len = 0;
	const char* pStr = static_cast<const char*>(pData);
	while (len < length)
		len += write(pStr + length, length - len);
}

size_t Process::read(void* pData, size_t length)
{
	ssize_t l = ::read(_fdBackward.GetReadPipe(), pData, length);
	std::cout << l << "\n";
	if (l == -1)
		throw std::runtime_error("An error occured!");
	return static_cast<size_t>(l);
}

void Process::readExact(void* pData, size_t length)
{
	size_t len = 0;
	char* pStr = static_cast<char*>(pData);
	while (len < length)
		len += read(pStr + len, length - len);
}

void Process::closeStdin()
{
	_fdForward.Close();
}

void Process::close()
{
	_fdForward.Close();
	_fdBackward.Close();

	int status;
	waitpid(_childPid, &status, WNOHANG);
	if (WIFEXITED(status)) return;
	kill(_childPid, SIGINT);
	waitpid(_childPid, nullptr, 0);
}