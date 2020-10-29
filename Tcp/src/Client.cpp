#include "Client.h"

namespace net
{
    Client::Client() {}

    Client::Client(std::unique_ptr<Connection> pConn)
    {
        _pConnection = std::move(pConn);
    }

    Client::Client(Client&& c)
    {
        _pConnection = std::move(c._pConnection);
    }

    Client::~Client()
    {
        Close();
    }

    Client& Client::operator = (Client&& c)
    {
        _pConnection = std::move(c._pConnection);
        return *this;
    }

    void Client::Close()
    {
        _pConnection->Close();
    }


    void Client::Connect(std::unique_ptr<Connection> pConn)
    {
        _pConnection = std::move(pConn);
    }

    size_t Client::Recv(void* pData, const size_t size)
    {
        ssize_t len = recv(_pConnection->Sock(), pData, size, 0);
        if (len == -1)
            throw std::runtime_error("Failed to receive a message!");
        return static_cast<size_t>(len);
    }

    size_t Client::Send(const void* pData, const size_t size)
    {
        ssize_t len = send(_pConnection->Sock(), pData, size, 0);
        if (len == -1)
            throw std::runtime_error("Failed to send a message!");
        return static_cast<size_t>(len);
    }

    void Client::RecvAll(void* pData, const size_t size)
    {
        size_t len = 0;
        char* pStr = static_cast<char*>(pData);
        while (len < size)
        {
            size_t l = Recv(pStr + len, size - len);
            if (l == 0) break;
            len += l;
        }
    }

    void Client::SendAll(const void* pData, const size_t size)
    {
        size_t len = 0;
        const char* pStr = static_cast<const char*>(pData);
        while (len < size)
        {
            size_t l = Send(pStr + len, size - len);
            if (l == 0) break;
            len += l;
        }
    }
}