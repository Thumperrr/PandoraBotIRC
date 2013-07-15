#include "irc/IRCMessage.hpp"
#include <iostream>

int main()
{
    //!< [example1]
    //Construct an IRCMessage from a raw irc message.
    std::string message = ":Thumperrr!~Thumperrr@ip184-180-235-145.mc.at.cox.net PRIVMSG #chessplusplus :I wonder if I could use them to parse IRC commands\r\n";
    std::cout << IRCMessage(message) << std::endl;
    //!< [example1]

    //!< [example2]
    //Parameter initialize an IRCMessage
    std::cout << IRCMessage("Me", "PRIVMSG", "#thisChannel", "IRCMessage is an awesome class.") << std::endl;
    //!< [example2]

    return 0;
}