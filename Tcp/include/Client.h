#pragma once
#include <memory>
#include "ConnectionUtils.h"

namespace net
{
    class Client
    {
        private:
        std::unique_ptr<Connection> _pConnection;

        public:
        Client();
        Client(std::unique_ptr<Connection> pConn);
        Client(const Client& c) = delete;
        Client(Client&& c);
        ~Client();

        Client& operator = (const Client& c) = delete;
        Client& operator = (Client&& c);

        void Connect(std::unique_ptr<Connection> pConn);
        void Close();

        size_t Recv(void* pData, const size_t size);
        size_t Send(const void* pData, const size_t size);
        void RecvAll(void* pData, const size_t size);
        void SendAll(const void* pData, const size_t size);
    };
}