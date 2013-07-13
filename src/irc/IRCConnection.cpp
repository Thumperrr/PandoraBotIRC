//
//  IRCConnection.cpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 7/12/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

#include "IRCConnection.hpp"

namespace pbirc { namespace irc {

	bool IRCConnection::connect(std::string const &server, std::uint16_t const &port)
	{
		m_server_name = server;
		m_port = port;

		return (m_status = (m_session.connect(server, port)));
	}

	void IRCConnection::disconnect()
	{
		m_status = false;
		m_session.disconnect();
	}

	IRCMessage IRCConnection::receive()
	{
        //if not connected return empty message
        if(!m_status) return IRCMessage();
        
        std::string recvd_data, current_msg;
        if(!(m_session >> recvd_data)) //if send fails, disconnect.
        {
            m_status = false;
            return IRCMessage();
        }
        m_data += recvd_data;
        
        std::size_t split_point = m_data.find("\n"); //find the end of one entire message
        if(split_point != std::string::npos)
        {
            current_msg = m_data.substr(0, split_point+1);
            m_data = m_data.substr(split_point+1, std::string::npos);
        }
        
        return IRCMessage(current_msg);
    }

    bool IRCConnection::send(IRCMessage const &msg)
    {
    	if(!m_status)
    		return false;

    	return (m_status = (m_session << msg.raw()));
    }

    void IRCConnection::work()
    {
    	IRCMessage msg = this->receive();
    	if(msg.empty())
    		return;

    	//find range of callbacks for this command
    	auto range = m_callback_map.equal_range(msg.command());
    	if(range.first != range.second) //at least one callback was found
    	{
    		for(auto i = range.first; i != range.second; ++i)
    			i->second(msg);
    	}
    	else //otherwise search for default callbacks
    	{
    		auto default_range = m_callback_map.equal_range("DEFAULT");
    		if(default_range.first != default_range.second)
    		{
    			for(auto i = default_range.first; i != default_range.second; ++i)
    				i->second(msg);
    		}
    	} //do nothing if no callbacks were found
    }

}}