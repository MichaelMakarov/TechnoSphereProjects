#pragma once
#include <netinet/in.h>
#include <string>

namespace net
{
    enum ConnectionType
    {
        TCP,
        UDP
    };

    class Connection
    {
        protected:
        int _sock;
        ConnectionType _type;

        virtual bool Connect(const std::string& addr, const ssize_t port) = 0;

        public:
        Connection(int sock);
        Connection(const std::string& addr, const ssize_t port);
        ~Connection();

        bool IsConnected();
        void Close();

        int Sock();

        ConnectionType Type();
    };
}