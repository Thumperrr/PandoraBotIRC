//
//  IRCConnection.hpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 7/12/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

#ifndef PandoraBotIRC_IRCConnection_hpp
#define PandoraBotIRC_IRCConnection_hpp

#include "TCPConnection.hpp"
#include "IRCMessage.hpp"

#include <functional>
#include <map>

namespace pbirc { namespace irc {

/*
 * @brief IRCConnection class represents a connection to an irc server.
 * 
 * @details This class can register callback functions to call when a certain
 *  command is received. 
 *  Call IRCConnection::work on every event loop of the program.
 *  IRCConnection will receive incoming messages, process them, and 
 *  call corresponding callback functions.
 *
 *  callback functions return type void, and have one parameter of type IRCMessage const &.
 *
 *  This funcitonality is entirely optional.
 *  You can use IRCConnection without using it's callback feature. 
 *  
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
    /*
     * Default constructor
     */
    IRCConnection() = default;

    /*
     * Default destructor
     */
    ~IRCConnection() = default;

    /*
     * Copy constructor is deleted
     */
    IRCConnection(IRCConnection const &) = delete;
    /*
     * Copy assignment is disabled
     */
    IRCConnection &operator=(IRCConnection const &);

    /*
     * Starts up a connection with an irc server
     *
     * @param[in] server domain name or IP address of the irc server
     * @param[in] port the port on the server to connect to
     */
    bool connect(std::string const &server, std::uint16_t const &port);

    /*
     * Disconnects from an irc server
     */
    void disconnect();

    /*
     * Receives data from the server and tries to format it into
     * an IRCMessage. Stores excess data in m_data for later access.
     *
     * Will set m_status to false and disconnect upon error.
     *
     * @return IRCMessage received from the server
     */
    IRCMessage receive();

    /*
     * Sends an IRCMessage to the server
     * Will set m_status to false and disconnect upon error.
     *
     * @param[in] msg IRCMessage object to be sent
     * @return true if everything worked and all is well
     *         false if otherwise
     */
    bool send(IRCMessage const &msg);

    /*
     * Operator bool
     * This function returns m_status
     *
     * Evaluates to true if all is good and we are connected to the server
     * Evaluates to false if we are disconnected or an error has occured
     */
    operator bool() { return m_status; }

    /*
     * @return name of the server that the object is connected to
     */
    std::string getServerName() const { return m_server_name; }

    /*
     * @return The port on the server the object is connected to
     */
    std::uint16_t getPort()     const { return m_port       ; }

    /*
     * Adds a callback function that is a member function of another object
     *
     * @param[in] cmd The command the callback function is connected to
     * @param[in] function the callback function
     * @param[in] object A pointer to the object the function belongs to
     */
    template<typename Func, typename Obj>
    void addCallback(std::string const &cmd, Func function, Obj object)
    {
        m_callback_map.insert(callback_map_t::value_type(cmd, std::bind(function, object, std::placeholders::_1)));
    }

    /*
     * Adds a callback function that is not a member function of another object
     *
     * @param[in] cmd The command the callback function is connected to
     * @param[in] function the callback function
     */
    template<typename Func>
    void addCallback(std::string const &cmd, Func function)
    {
        m_callback_map.insert(callback_map_t::value_type(cmd, std::bind(function, std::placeholders::_1)));
    }

    /*
     * This is the main worker function when using callback functionality.
     * This function tries to receive a message from the server,
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