#include "Connection.h"
#include <stdexcept>
#include <unistd.h>

namespace net
{
    Connection::Connection(int sock)
    {
        _sock = sock;
    }

    Connection::Connection(const std::string& addr, const ssize_t port)
    {
        if (Connect(addr, port))
            throw std::runtime_error("Failed to connect!");
    }

    bool Connection::IsConnected()
    {
        return _sock > 0;
    }

    void Connection::Close()
    {
        close(_sock);
        _sock = -1;
    }

    int Connection::Sock()
    {
        return _sock;
    }

    ConnectionType Connection::Type()
    {
        return _type;
    }
}