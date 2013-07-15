#include "irc/TCPConnection.hpp"
#include <iostream>

int main()
{
    //Example connects to irc.freenode.net on port 6667.
    //Should be able to receive some data before the connection times out.
    pbirc::irc::TCPConnection connection;
    if(!connection.connect("irc.freenode.net", 6667)
    {
        std::cout << "Error on connecting." << std::endl;
        return -1;
    }

    //receive data until an error occurs or the socket is disconneted.
    std::string str;
    while(connection >> str)
    {
        std::cout << str;
    }

    return 0;
}

/**
 [output]
 [output]
 */