#include "TcpConnection.h"
#include <arpa/inet.h>

namespace net
{
    TcpConnection::TcpConnection(TcpConnection&& c) : Connection(c._sock)
    {
        c._sock = -1;
        _type = ConnectionType::TCP;
    }

    TcpConnection& TcpConnection::operator = (TcpConnection&& c)
    {
        _sock = c._sock;
        _type = ConnectionType::TCP;
        c._sock = -1;
        return *this;
    }

    TcpConnection::~TcpConnection() {}

    bool TcpConnection::Connect(const std::string& addr, const ssize_t port)
    {
        _sock = socket(AF_INET, SOCK_STREAM, 0);
        if (_sock < 0) return false;
        sockaddr_in addrin = { 0 };
        addrin.sin_family = AF_INET;
        addrin.sin_port = htons(static_cast<uint16_t>(port));
        if (inet_pton(AF_INET, addr.c_str(), &addrin.sin_port) <= 0)
            return false;
        return connect(_sock, reinterpret_cast<sockaddr*>(&addrin), sizeof(addrin)) == 0;
    }
}