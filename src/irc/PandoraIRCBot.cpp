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
        m_session.send(IRCMessage("", "PRIVMSG", msg.params(), m_bot.think(msg.data())));
    }

    void PandoraIRCBot::onPING(IRCMessage const &msg)
    {
        m_session.send(IRCMessage("", "PONG", "", msg.data()));
    }

    void PandoraIRCBot::onDEFAULT(IRCMessage const &msg)
    {
        std::cout << msg.raw();
    }

    void PandoraIRCBot::_Init()
    {
        m_session.addCallback("PRIVMSG", &PandoraIRCBot::onPRIVMSG, this);
        m_session.addCallback("PING",    &PandoraIRCBot::onPING,    this);
        m_session.addCallback("DEFAULT", &PandoraIRCBot::onDEFAULT, this);
    }

}}