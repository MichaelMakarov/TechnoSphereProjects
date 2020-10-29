#pragma once
#include "Connection.h"

namespace net
{
    class TcpConnection : public Connection
    {
        protected:
        bool Connect(const std::string& addr, const ssize_t port) override;

        public:
        using Connection::Connection;
        TcpConnection(const TcpConnection& c) = delete;
        TcpConnection(TcpConnection&& c);
        ~TcpConnection();

        TcpConnection& operator = (const TcpConnection& c) = delete;
        TcpConnection& operator = (TcpConnection&& c);
    };
}