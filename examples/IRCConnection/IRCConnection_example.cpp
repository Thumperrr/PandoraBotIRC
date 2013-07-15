#include "irc/IRCConnection.hpp"
#include "irc/IRCMessage.hpp"

using pbirc::irc::IRCMessage;

void onNotice(IRCMessage const &msg)
{
    std::cout << "Notice: " << msg.data() << std::endl;
}
void onDefault(IRCMessage const &msg)
{
    std::cout << "DEFAULT: " << msg.data() << std::endl;
}

int main()
{
    pbirc::irc::IRCConnection irc;
    if(!irc.connect("irc.freenode.net", 6667))
    {
        std::cout << "Error connecting." << std::endl;
        return -1;
    }

    //register callbacks
    irc.addCallback("NOTICE", &onNotice);
    irc.addCallback("DEFAULT", &onDefault);

    // If the callback is a member function, addCallback requires a pointer to the object.
    // Ex: addCallback("NOTICE", &ObjectName::onNotice, ptrToObject);
    //     ptrToObject is usually the this pointer.
    while(irc)
    {
        irc.work();
    }

    return 0;
}