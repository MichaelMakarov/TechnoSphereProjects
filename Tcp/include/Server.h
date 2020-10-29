#pragma once
#include "Client.h"

namespace net
{
    class Server
    {
        private:
        std::unique_ptr<Connection> _pListener;
        size_t _size;

        public:
        Server();
        Server(std::unique_ptr<Connection> pConn, const size_t queueSize);
        Server(const Server& s) = delete;
        Server(Server&& s);
        ~Server();

        Server& operator = (const Server& s) = delete;
        Server& operator = (Server&& s);

        void Listen(std::unique_ptr<Connection> pConn, const size_t queueSize);
        void Listen();
        std::unique_ptr<Client> Accept();
        void Close();

        void SetQueueSize(const size_t queueSize);
        void SetTimeout(const size_t time);

    };
}