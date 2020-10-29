#include "ConnectionUtils.h"

namespace net
{
    std::unique_ptr<Connection> GetConnectionPtr(const int sock, const ConnectionType type)
    {
        switch (type)
        {
            case ConnectionType::TCP:
                return std::unique_ptr<Connection>(new TcpConnection(sock));
            case ConnectionType::UDP:
                throw std::runtime_error("Not implemented!");
        }
        return nullptr;
    }
}