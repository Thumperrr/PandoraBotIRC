//
//  PandoraIRCBot.cpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 7/12/13.
//////////////////////////////////////////////////////////////////////////////////
//  The MIT License (MIT)
//
//  Copyright (c) 2013 Stephen Hall
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////


#include "PandoraIRCBot.hpp"

namespace pbirc { namespace irc {

    PandoraIRCBot::PandoraIRCBot(std::string const &server, std::uint16_t const &port, std::string const &nick, std::string const &chan)
    : m_server(server)
    , m_nick(nick)
    , m_channel(chan)
    , m_port(port)
    {
        _Init();
    }

    bool PandoraIRCBot::connect()
    {
        if(m_server.empty() || m_nick.empty() || m_channel.empty()) 
            return false;

        if(m_session.connect(m_server, m_port))
        {
            m_session.send(IRCMessage("", "USER", m_nick + " 0 *", m_nick));
            m_session.send(IRCMessage("", "NICK", m_nick, ""));
            m_session.send(IRCMessage("", "JOIN", "", m_channel));
        }

        return m_session;
    }

    void PandoraIRCBot::disconnect()
    {
        m_session.disconnect();
    }

    int PandoraIRCBot::run()
    {
        if(this->connect())
        {
            while(m_session)
                m_session.work();
        }
        else return -1;

        return 0;
    }

    void PandoraIRCBot::onPRIVMSG(IRCMessage const &msg)
    {
        //Check for commands
        if(msg.data().find("!BotQuit") != std::string::npos)
        {
            m_session.disconnect();
        }
        else if(msg.data().find("!BotHalt") != std::string::npos)
        {
            m_halt = true;
        }
        else if(msg.data().find("!BotResume") != std::string::npos)
        {
            m_halt = false;
        }
        else if(msg.data().find("!BotTalk") != std::string::npos) //start conversation with user
        {
            m_conversations.insert({msg.sender(), cb::PandoraBot(botid_default)});
            privmsg(msg.params(), "Hello there!");
        }
        else if(msg.data().find("!BotStop") != std::string::npos)
        {
            auto i = m_conversations.find(msg.sender());
            if(i != m_conversations.end())
            {
                m_conversations.erase(msg.sender());
                privmsg(msg.params(), "Fine, I was done talking to you anyway.");
            }
        }
        else if(msg.data().find("!BotHelp") != std::string::npos)
        {
            privmsg(msg.params(), "PandoraBotIRC: An irc bot that acts as a Pandora chatter bot.");
            privmsg(msg.params(), "Command list:");
            privmsg(msg.params(), "!BotQuit -- Shuts the bot down.");
            privmsg(msg.params(), "!BotHalt -- Puts the bot in an idle state. Continues running but doesn't reply to anyone.");
            privmsg(msg.params(), "!BotResume -- Resumes the bot after !BotHalt has been called.");
            privmsg(msg.params(), "!BotTalk -- Start a conversation with the bot! The bot will start responding to things you type.");
            privmsg(msg.params(), "!BotStop -- Stop the bot from talking to you.");
            privmsg(msg.params(), "!BotID <bot_id> -- Changes the bot you are talking to. ID's can be retrieved from www.pandorabots.com");
            privmsg(msg.params(), "!BotHelp -- Display this message.");
        
        }
        else if(msg.data().find("!BotID") != std::string::npos)
        {
            //botid's are 16 characters in length
            std::string botid = msg.data().substr(msg.data().find("!BotID")+7, 16);
            std::cout << "Changed botid: " << botid << std::endl;

            auto i = m_conversations.find(msg.sender());
            if(i != m_conversations.end())
            {
                m_conversations.erase(msg.sender());
                m_conversations.insert({msg.sender(), cb::PandoraBot(botid)});
            }
        }
        else
        {
            if(!m_halt)
            {
                auto i = m_conversations.find(msg.sender());
                if(i != m_conversations.end())
                {
                    std::string nick = i->first.substr(0, i->first.find("!"));
                    privmsg(msg.params(), nick + ", " + i->second.think(msg.data()));
                }
            }
        }
    }

    void PandoraIRCBot::onPING(IRCMessage const &msg)
    {
        m_session.send(IRCMessage("", "PONG", "", msg.data()));
    }

    void PandoraIRCBot::onALL(IRCMessage const &msg)
    {
        std::cout << msg.raw();
    }

    void PandoraIRCBot::_Init()
    {
        m_halt = false;
        m_session.addCallback("PRIVMSG", &PandoraIRCBot::onPRIVMSG, this);
        m_session.addCallback("PING",    &PandoraIRCBot::onPING,    this);
        m_session.addCallback("ALL",     &PandoraIRCBot::onALL,     this);
    }

    void PandoraIRCBot::privmsg(std::string const &channel, std::string const &msg)
    {
        m_session.send(IRCMessage("", "PRIVMSG", channel, msg));
    }

}}