#include "irc/PandoraIRCBot.hpp"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <string>

void printUsage(std::ostream &os)
{
    os << "Usage: <server> <port> <nick> <channel>." << std::endl;
    os << "\tAll fields are required." << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc < 5)
    {
        std::cout << "Error: Invalid number of parameters" << std::endl;
        printUsage(std::cout);
        return -1;
    }
    pbirc::irc::PandoraIRCBot bot(argv[1],
                                  boost::lexical_cast<int>(argv[2]), 
                                  argv[3], 
                                  "#" + std::string(argv[4]));

    return bot.run();
}