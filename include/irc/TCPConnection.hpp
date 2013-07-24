//
//  TCPConnection.hpp
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
#ifndef PandoraBotIRC_TCPConnection_hpp
#define PandoraBotIRC_TCPConnection_hpp

#include <SFML/Network.hpp>

#include <cstdint>
#include <string>
#include <array>

namespace pbirc { namespace irc {

/**
 * @brief TCPConnection encapsulates a tcp connection with SFML sockets
 * @section TCPConnection_ex1 Example Usage
 * @include TCPConnection/TCPConnection_example.cpp
 * Possible output for the above example:
 * @verbinclude TCPConnection/TCPConnection_example_output.txt
 */
class TCPConnection
{
    //maximum amount of data received at once. 
    static const unsigned int receive_buff_sz = 256;

    sf::TcpSocket m_socket;
    bool          m_status; 

public:
    /**
     * @brief Default constructor. 
     * @details Does nothing but set 'm_status' to false.
     */
    TCPConnection();

    /**
     * @brief Default destructor
     */
    ~TCPConnection() = default;

    //Copying of tcp connections is disabled
    TCPConnection(TCPConnection const &) = delete;
    TCPConnection &operator=(TCPConnection const &);

    /**
     * @brief Starts up the tcp connection
     *
     * @param[in] server_name domain name or IP of the server to connect to
     * @param[in] port the port on the server to connect to
     */
    bool connect(std::string const &server_name, std::uint16_t const &port);

    /**
     * @brief Disconnects the tcp connection. 
     */
    void disconnect();

    /**
     * @brief Get the port to which the socket is bound locally.
     * @details This function only forwards sf::Socket::getLocalPort().
     *
     * @return uint16_t representing the local port.
     */
    std::uint16_t getLocalPort();

    /**
     * @brief Get the port of the connected peer to which the socket is connected.
     * @details This function only forwards sf::Socket::getRemotePort().
     *
     * @return uint16_t representing the remote port.
     */
    std::uint16_t getRemotePort();

    /**
     * @brief operator bool
     * This function returns m_status. 
     * 
     * @details Evaluates to true if all is good and the socket is connected.
     * Evaluates to false if something has gone wrong or if the socket is disconnected.
     */
    operator bool() { return m_status; }

    /**
     * @brief operator << overload.
     * @details Is used to send data to the server.
     * This function will disconnect and set m_status to false upon error.
     *
     * Ex: connection << "This is some text that will be sent to the server";
     */
    TCPConnection &operator<<(std::string const &rhs);

    /**
     * @brief operator >> overload.
     * @details Is used to receive data from the server.
     * This function will disconnect and set m_status to false upon error.
     * The amount of data received at once by this function is limited by 'receive_buff_sz'.
     * A received string will never be more than 'receive_buff_sz' characters in length, but may be less.
     *
     * Ex: std::string data; connection >> data;
     */
    TCPConnection &operator>>(std::string       &rhs);
};

}}
#endif