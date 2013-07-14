//
//  IRCBot.hpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 7/13/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

#ifndef PandoraBotIRC_IRCBot_hpp
#define PandoraBotIRC_IRCBot_hpp

namespace pbirc { namespace irc {

/**
 * @brief Abstract base class representing an IRC bot. 
 * 
 * @details Has three functions that base classes must overload:
 * connect()
 * disconnect()
 * run()
 */
class IRCBot
{
public:
    /**
     * @brief Default constructor
     */
    IRCBot() = default;

    /**
     * @brief Virtual default destructor
     */
    virtual ~IRCBot() = default;

    /**
     * @brief esponsible for connecting to the irc server
     * and starting up the bot.
     */
    virtual bool connect() = 0;

    /**
     * @brief Responsible for disconnecting from the server
     * and stopping the bot
     */
    virtual void disconnect() = 0;

    /**
     * @brief Worker function for the bot. Responsible for doing
     * everything else that the bot should do.
     */
    virtual int run() = 0;
};

}}
#endif