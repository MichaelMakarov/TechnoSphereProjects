#pragma once
#include "TcpConnection.h"
#include <memory>

namespace net
{
    std::unique_ptr<Connection> GetConnectionPtr(const int sock, const ConnectionType type);
}