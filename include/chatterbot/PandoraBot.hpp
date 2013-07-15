//
//  PandoraBot.hpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 6/29/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

#ifndef PandoraBotIRC_PandoraBot_hpp
#define PandoraBotIRC_PandoraBot_hpp

#include "ChatterBot.hpp"

namespace pbirc { namespace cb {
    
/**
 * @brief Class representing a connection to a PandoraBot chatterbot.
 * @details Call PandoraBot::think with a message, and it will return a reply. 
 *
 * @section pandorabot_ex1 Example Usage
 * @include PandoraBot/PandoraBot_example.cpp
 *
 * @section pandorabot_ex2 A word on BotIDs
 * Bot IDs are found from www.pandorabots.com
 * You can browse through bots on that website (there are many.)
 * When you find a bot you want to use, click on it, and the botid will be in the url.
 * 
 * BotIDs are 16 characters in length.
 * Using an incorrect BotID will result in undefined behavior. 
 */
class PandoraBot : public ChatterBot
{
    std::string m_botid, m_custid;
    
public:
    /**
     * @brief Default ctor deleted. Must provide a botid for PandoraBot to function.
     */
    PandoraBot() = delete;
    
    /**
     * @brief PandoraBot constructor. 
     *
     * @param[in] botid An ID representing which Pandora Bot to connect with
     */
    PandoraBot(std::string const &botid);
    
    /**
     * @brief Function for talking with the Pandora Bot.
     *
     * @param msg A message to send to the bot
     * @return The bot's reply
     */
    std::string think(std::string const &msg);
    
private:
    /**
     * @brief Responsible for processing received data from the Pandora Bot.
     * @details Sometimes the message will contain HTML, or HTML escape characters
     * that need to be removed. 
     *
     * @param[in] s string to be processed
     * @return processed string
     */
    std::string process_input(std::string const &s);
};
    
}}
#endif
