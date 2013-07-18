//
//  PandoraIRCBot.hpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 7/13/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

#ifndef PandoraBotIRC_PandoraIRCBot_hpp
#define PandoraBotIRC_PandoraIRCBot_hpp

#include "IRCBot.hpp"
#include "IRCMessage.hpp"
#include "IRCConnection.hpp"
#include "chatterbot/PandoraBot.hpp"

#include <cstdint>
#include <string>
#include <map>

namespace pbirc { namespace irc {

/**
 * @brief Class representing a Pandora IRC bot. 
 * @details his bot will connect to an IRC server
 * and respond to users as a Pandora chatterbot.
 * 
 * @section Example Usage
 * Refer to the following snippet from main.cpp:
 * @snippet main.cpp PandoraIRCBot usage
 */
class PandoraIRCBot : public IRCBot
{
    typedef std::map<std::string, cb::PandoraBot> conversations_t;
    const std::string botid_default{"831d7b032e345b1f"};

    std::string m_server, m_nick, m_channel;
    std::uint16_t m_port;

    bool m_halt; //!< True if the bot is disabled. False otherwise.

    IRCConnection   m_session;       //!< tcp session with the irc server
    conversations_t m_conversations; //!< Key: user name. Value: Pandora bot. 

public:
    /**
     * @brief Default constructor
     */
    PandoraIRCBot() { _Init(); }

    /**
     * @brief Default destructor
     */
    virtual ~PandoraIRCBot() = default;

    /**
     * @brief Value initialized constructor
     *
     * @param[in] server the irc server to connect to
     * @param[in] port the port on the irc server to connect to
     * @param[in] nick the nick the bot should use on the irc server.
     * @param[in] chan the channel the bot should connect to
     */
    PandoraIRCBot(std::string const &server, std::uint16_t const &port, std::string const &nick, std::string const &chan);

    /**
     * @brief Copy constructor deleted
     */
    PandoraIRCBot(PandoraIRCBot const &) = delete;

    /**
     * @brief Copy assignment disabled
     */
    PandoraIRCBot &operator=(PandoraIRCBot const &);

    /**
     * @brief Responsible for connecting to the irc server
     */
    bool connect() override;

    /**
     * @brief Responsible for disconnecting from the irc server
     */
    void disconnect() override;

    /**
     * @brief Main worker function. Responsible for doing everything the bot needs to do.
     */
    int run() override;

    void setServer (std::string   const &server) { m_server = server; } //!< sets server
    void setNick   (std::string   const &nick  ) { m_nick = nick;     } //!< sets nick
    void setPort   (std::uint16_t const &port  ) { m_port = port;     } //!< sets port
    void setChannel(std::string const &chan    ) { m_channel = chan;  } //!< sets channel

    std::string   getServer()  const { return m_server; } //!< Gets server
    std::string   getNick()    const { return m_nick;   } //!< Gets nick
    std::uint16_t getPort()    const { return m_port;   } //!< Gets port
    std::string   getChannel() const { return m_channel;} //!< Gets channel
public: //CALLBACKS DEFINED HERE

    /**
     * @brief this callback handles PRIVMSG commands sent from the server
     * @details Responds with PandoraBot response
     */
    void onPRIVMSG(IRCMessage const &msg);

    /**
     * @brief this callback handles PING commands sent from the server
     * @details Responds with PONG
     */
    void onPING(IRCMessage const &msg);

    /**
     * @brief this callback handles PART commands.
     * @details Says something vulgar about a user after he leaves.
     * @bug not yet implemented.
     */
    void onPART(IRCMessage const &msg);
    
    /**
     * @brief ALL callback. All messages go through this function.
     * @details Currently outputs them in the terminal.
     */
    void onALL(IRCMessage const &msg);

private:
    /**
     * @brief This function does initialization tasks for PandoraIRCBot
     * @details Registers callbacks with m_session.
     */
    void _Init();

    /**
     * @brief Sends a private message to the server
     * @details privmsgs were being sent so much in this class
     * so it made sense to make a function for it to save some typing.
     *
     * @param[in] channel The channel the privmsg should be sent to. (goes in IRCMessage::params field)
     * @param[in] msg The privmsg
     */
    void privmsg(std::string const &channel, std::string const &msg);
};

}}
#endif