//
//  IRCConnection.hpp
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

#ifndef PandoraBotIRC_IRCConnection_hpp
#define PandoraBotIRC_IRCConnection_hpp

#include "TCPConnection.hpp"
#include "IRCMessage.hpp"

#include <functional>
#include <map>

namespace pbirc { namespace irc {

/**
 * @brief IRCConnection class represents a connection to an irc server.
 * 
 * @details This class can register callback functions to call when a certain
 *  command is received.\n
 *  Call IRCConnection::work on every event loop of the program.\n
 *  IRCConnection will receive incoming messages, process them, and 
 *  call corresponding callback functions.
 *
 *  callback functions return type void, and have one parameter of type IRCMessage const &.
 *
 *  This funcitonality is entirely optional.
 *  You can use IRCConnection without using it's callback feature. 
 *  
 *  There are two built in special callback keys that aren't IRC commands.\n
 *  1.) "ALL" -- Callbacks registered with this key are executed for every command.\n
 *  2.) "DEFAULT" -- Callbacks registered with this key are executed if no other callbacks exist for the command.\n
 *
 * @section IRCConnection Example
 * @include IRCConnection/IRCConnection_example.cpp
 * Possible output for the above code:
 * @verbinclude IRCConnection/IRCConnection_example_output.txt
 */
class IRCConnection
{
    typedef std::function<void(IRCMessage const &)> callback_t;     //typedef for callback functions
    typedef std::multimap<std::string, callback_t>  callback_map_t; //typedef for callback container

    callback_map_t m_callback_map;

    std::string m_data, m_server_name;
    std::uint16_t m_port;

    bool m_status;

    TCPConnection m_session;

public:
    /**
     * @brief Default constructor
     */
    IRCConnection() = default;

    /**
     * @brief Default destructor
     */
    ~IRCConnection() = default;

    /**
     * @brief Copy constructor is deleted
     */
    IRCConnection(IRCConnection const &) = delete;
    /**
     * @brief Copy assignment is disabled
     */
    IRCConnection &operator=(IRCConnection const &);

    /**
     * @brief Starts up a connection with an irc server
     *
     * @param[in] server domain name or IP address of the irc server
     * @param[in] port the port on the server to connect to
     */
    bool connect(std::string const &server, std::uint16_t const &port);

    /**
     * @brief Disconnects from an irc server
     */
    void disconnect();

    /**
     * @brief Receives data from the server and tries to format it into
     * an IRCMessage. 
     * @details Stores excess data in m_data for later access.
     * Will set m_status to false and disconnect upon error.
     *
     * @return IRCMessage received from the server
     */
    IRCMessage receive();

    /**
     * @brief Sends an IRCMessage to the server
     * @details Will set m_status to false and disconnect upon error.
     *
     * @param[in] msg IRCMessage object to be sent
     * @return true if everything worked and all is well
     *         false if otherwise
     */
    bool send(IRCMessage const &msg);

    /**
     * @brief Operator bool
     * This function returns m_status
     *
     * @details
     * Evaluates to true if all is good and we are connected to the server
     * Evaluates to false if we are disconnected or an error has occured
     */
    operator bool() { return m_status; }

    /**
     * @return name of the server that the object is connected to
     */
    std::string getServerName() const { return m_server_name; }

    /*
     * @return The port on the server the object is connected to
     */
    std::uint16_t getPort()     const { return m_port       ; }

    /**
     * @brief Adds a callback function that is a member function of another object
     *
     * @param[in] cmd The command the callback function is connected to
     * @param[in] function the callback function
     * @param[in] object A pointer to the object the function belongs to
     */
    template<typename Func, typename Obj>
    void addCallback(std::string const &cmd, Func function, Obj object)
    {
        m_callback_map.insert({cmd, std::bind(function, object, std::placeholders::_1)});
    }

    /**
     * @brief Adds a callback function that is not a member function of another object
     *
     * @param[in] cmd The command the callback function is connected to
     * @param[in] function the callback function
     */
    template<typename Func>
    void addCallback(std::string const &cmd, Func function)
    {
        m_callback_map.insert({cmd, std::bind(function, std::placeholders::_1)});
    }

    /**
     * @brief This is the main worker function when using callback functionality.
     * @details This function tries to receive a message from the server,
     * format it into an IRCMessage object
     * then call the corresponding callbacks for the message.
     *
     * If no corresponding callback is found for the message, work will try use a 
     * callback registered with the "DEFAULT" command.
     * If no callback is found, the message is dropped.
     * 
     * When using callbacks, 'work' should be called on every event loop of the program.
     */
    void work();


};

}}
#endif