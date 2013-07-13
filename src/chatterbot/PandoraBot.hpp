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
    
    /*
     * Class representing a connection to a PandoraBot chatterbot.
     * Call PandoraBot::think with a message, and it will return a reply. 
     */
    class PandoraBot : public ChatterBot
    {
        std::string m_botid, m_custid;
        
    public:
        /*
         * Default ctor deleted. Must provide a botid for PandoraBot to function.
         */
        PandoraBot() = delete;
        
        /*
         * PandoraBot constructor. 
         *
         * @param[in] botid An ID representing which Pandora Bot to connect with
         */
        PandoraBot(std::string const &botid);
        
        /*
         * Function for talking with the Pandora Bot.
         *
         * @param msg A message to send to the bot
         * @return The bot's reply
         */
        std::string think(std::string const &msg);
        
    private:
        /*
         * Responsible for processing received data from the Pandora Bot.
         * Sometimes the message will contain HTML, or HTML escape characters
         * that need to be removed. 
         *
         * @param[in] s string to be processed
         * @return processed string
         */
        std::string process_input(std::string const &s);
    };
    
}}
#endif
