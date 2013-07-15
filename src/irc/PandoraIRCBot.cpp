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
            m_conversations.insert(conversations_t::value_type(msg.sender(), cb::PandoraBot(botid_default)));
        }
        else if(msg.data().find("!BotStop") != std::string::npos)
        {
            m_conversations.erase(msg.sender());
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
            privmsg(msg.params(), "!BotHelp -- Display this message.");
        
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