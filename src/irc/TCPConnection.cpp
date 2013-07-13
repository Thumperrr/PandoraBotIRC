//
//  TCPConnection.cpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 7/12/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

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
        m_status = (m_socket.send(rhs.c_str(), rhs.size()) != sf::Socket::Status::Disconnected);

        //something went wrong, disconnect.
        if(!m_status) m_socket.disconnect();

        return *this;
    }

    TCPConnection &TCPConnection::operator>>(std::string &rhs)
    {
        std::array<char, receive_buff_sz> buffer;
        std::size_t bytes_recvd;

        m_status = (m_socket.receive(&buffer.front(), receive_buff_sz, bytes_recvd) != sf::Socket::Status::Disconnected);

        if(m_status) //all is good
            rhs = std::string(buffer.begin(), bytes_recvd);

        return *this;
    }

}}