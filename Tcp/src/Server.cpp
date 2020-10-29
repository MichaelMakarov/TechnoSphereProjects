#include "Server.h"
#include "unistd.h"

namespace net
{
    Server::Server()
    {
        _pListener = nullptr;
        _size = 0;
    }

    Server::Server(std::unique_ptr<Connection> pConn, const size_t queueSize)
    {
        _pListener = std::move(pConn);
        _size = queueSize;
    }

    Server::Server(Server&& s) 
    {
        _pListener = std::move(s._pListener);
        _size = s._size;
    }

    Server::~Server()
    {
        Close();
    }

    Server& Server::operator = (Server&& s)
    {
        _pListener = std::move(s._pListener);
        _size = s._size;
        return *this;
    }

    void Server::Listen()
    {
        if (listen(_pListener->Sock(), _size) == -1)
            throw std::runtime_error("Failed to listen!");
    }

    void Server::Listen(std::unique_ptr<Connection> pConn, const size_t queueSize)
    {
        _pListener = std::move(pConn);
        _size = queueSize;
        Listen();
    }

    std::unique_ptr<Client> Server::Accept()
    {
        int sock = accept(_pListener->Sock(), nullptr, nullptr);
        if (sock == -1)
            throw std::runtime_error("Failed to accept connection!");
        return std::unique_ptr<Client>(new Client(GetConnectionPtr(sock, _pListener->Type())));
    }

    void Server::Close()
    {
        _pListener->Close();
    }

    void Server::SetQueueSize(const size_t size)
    {
        _size = size;
    }

    void Server::SetTimeout(const size_t time)
    {
        
    }
}