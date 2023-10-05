#ifndef _WEB_  
#define _WEB_

#include "../server/server.hpp"
#include "Handlers.hpp"
#include "Utaxi.hpp"

class Web
{
public:
    Web(int port);
    void run(std::string file_address);

private:
    Server server;
    Utaxi* utaxi;
};


#endif