//
//  IRCMessage.hpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 7/12/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

#ifndef PandoraBotIRC_IRCMessage_hpp
#define PandoraBotIRC_IRCMessage_hpp

#include "util/Utility.hpp"

#include <string>
#include <exception>

namespace pbirc { namespace irc {

/**
 * @brief IRCMessage class represents an IRC message that corresponds with irc protocol.
 * @details IRC messages come in the form of ":<sender> <command> <params> :<data>\r\n"
 *  there may be multiple params, and data can be of any length. 
 *  Sender, params, and data are optional fields.
 *
 *  IRCMessage may be constructed by raw IRC messages received from a server.
 *  This method will throw std::invalid_argument if the string supplied does not match
 *  the format of an IRC message.
 *
 *  A more detailed description of IRCMessage can be found at
 *  https://gist.github.com/Thumperrr/e35f7b45e116624b5bae
 */
class IRCMessage
{
    std::string m_sender, m_command, m_params, m_data;

public:
    /**
     * @brief Default constructor
     */
    IRCMessage() = default;
    /**
     * @brief Default destructor
     */
    ~IRCMessage() = default;

    /**
     * @brief Constructor (1) - Paremeter initialized.
     *
     * @param[in] sender a string that contains the sender bit of the message
     * @param[in] command a string that contains the command bit of the message
     * @param[in] params a string that contains the parameters bit of the message
     * @param[in] data a string that contains the data bit of the message.
     */
    IRCMessage(std::string const &sender, std::string const &command, std::string const &params, std::string const &data);

    /**
     * @brief Constructor (2) - Raw message initialized.
     * @details This constructor takes a raw message received from an irc server
     * and fills out the object accordingly.
     * 
     * This constructor will throw std::invalid_argument if raw does not
     * match the format of an irc message.
     * 
     * @param[in] raw string that contains the raw irc protocol message
     */
    explicit IRCMessage(std::string const &raw);

    /**
     * @brief Copy constructor is defaulted.
     */
    IRCMessage(IRCMessage const &) = default;

    /**
     * @brief Assignment operator allows assignment between IRCMessages
     */
    IRCMessage &operator=(IRCMessage const &rhs);

    /**
     * @brief Comparison operator allows comparison of IRCMessages
     */
    bool operator==(IRCMessage const &rhs);

    std::string sender()  const { return m_sender;  } //!< Gets sender
    std::string command() const { return m_command; } //!< Gets command
    std::string params()  const { return m_params;  } //!< Gets params
    std::string data()    const { return m_data;    } //!< Gets data

    void setSender (std::string const &sender ) { m_sender = sender;   } //!< Sets sender
    void setCommand(std::string const &command) { m_command = command; } //!< Sets command
    void setParams (std::string const &params ) { m_params = params;   } //!< Sets params
    void setData   (std::string const &data   ) { m_data = data;       } //!< Sets data

    /**
     * @brief Uses varargs to add parameters.
     * 
     * @details Allows for the syntax: addParams("Param1", "Param2", "Param3", ...).
     * in the event that parameters need to be added one by one. 
     * (setParams does not allow this)
     */
    template<typename... Params>
    void addParams(std::string const &head, Params const &... tail)
    {
        m_params += m_params.empty() ? "" : " ";
        m_params += head;
        addParams(tail...);
    }
    /**
     * @brief Edge condition for the recursive @link addParams addParams @endlink
     */
    void addParams() {}

    /**
     * @return true if the object is empty
     *         false otherwise.
     */
    bool empty() const;

    /**
     * @return the raw irc protocol message equivalent to the object.
     */
    std::string raw() const;

private:
    /**
     * @brief Formats input -- Removes trailing spaces left from regex matches.
     */
    std::string process_input(std::string const &str) { return util::removeTrailingSpaces(str); }
};

/**
 * @relates IRCMessage
 * @brief Global std::ostream operator<< overload for IRCMessages
 * @details
 *  Outputs the IRC message in the following format:
 * @code
 *  Sender: 
 *  Command:
 *  Params:
 *  Data:
 * @endcode
 */
std::ostream &operator<<(std::ostream &os, IRCMessage const &rhs);

}}
#endif