//
//  TCPConnection.cpp
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

#include "TCPConnection.hpp"

namespace pbirc { namespace irc {

    TCPConnection::TCPConnection()
    : m_status(false)
    {
    }

    bool TCPConnection::connect(std::string const &server_name, std::uint16_t const &port)
    {
        m_status = (m_socket.connect(sf::IpAddress(server_name), port) == sf::Socket::Status::Done);
        if(!m_status)
            return m_status;

        m_socket.setBlocking(false);
        return m_status;
    }

    void TCPConnection::disconnect()
    {
        m_socket.disconnect();
        m_status = false;
    }

    std::uint16_t TCPConnection::getLocalPort()
    {
        return m_socket.getLocalPort();
    }
    std::uint16_t TCPConnection::getRemotePort()
    {
        return m_socket.getRemotePort();
    }

    TCPConnection &TCPConnection::operator<<(std::string const &rhs)
    {
        auto status = m_socket.send(rhs.c_str(), rhs.size());
        m_status = (status != sf::Socket::Status::Disconnected && status != sf::Socket::Status::Error);

        //something went wrong, disconnect.
        if(!m_status) m_socket.disconnect();

        return *this;
    }

    TCPConnection &TCPConnection::operator>>(std::string &rhs)
    {
        std::array<char, receive_buff_sz> buffer;
        std::size_t bytes_recvd;

        auto status = m_socket.receive(&buffer.front(), receive_buff_sz, bytes_recvd);
        m_status = (status != sf::Socket::Status::Disconnected && status != sf::Socket::Status::Error);

        if(m_status) //all is good
            rhs = std::string(buffer.begin(), bytes_recvd);

        return *this;
    }

}}