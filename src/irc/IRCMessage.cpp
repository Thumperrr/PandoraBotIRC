//
//  IRCMessage.cpp
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

#include "IRCMessage.hpp"

namespace pbirc { namespace irc {

    IRCMessage::IRCMessage(std::string const &sender, std::string const &command, std::string const &params, std::string const &data)
    : m_sender(sender)
    , m_command(command)
    , m_params(params)
    , m_data(data)
    {
    }

    IRCMessage::IRCMessage(std::string const &raw)
    {
        if(raw.empty()) return; //string is empty
        if(raw.find(' ') == std::string::npos) //string only contains command
        {
            m_command = raw;
            return;
        }

        static boost::regex const regex("^(:(\\S+ ))?(\\S+ )((?!:).+?)?(:(.+))?(\r\n)?$");
        boost::smatch match;

        if(boost::regex_match(raw, match, regex))
        {
            m_sender  = process_input(match[2]);
            m_command = process_input(match[3]);
            m_params  = process_input(match[4]);
            m_data    = process_input(match[6]);
        }
        else throw std::invalid_argument("Unable to match the following string to irc protocol regex: " + raw);
    }

    IRCMessage &IRCMessage::operator=(IRCMessage const &copy)
    {
        m_sender  = copy.m_sender;
        m_command = copy.m_command;
        m_params  = copy.m_params;
        m_data    = copy.m_data;
        return *this;
    }

    bool IRCMessage::operator==(IRCMessage const &rhs)
    {
        return m_sender == rhs.m_sender && m_command == rhs.m_command
            && m_params == rhs.m_params && m_data    == rhs.m_data;
    }

    bool IRCMessage::empty() const
    {
        return m_sender.empty() && m_command.empty()
            && m_params.empty() && m_data.empty();
    }

    std::string IRCMessage::raw() const
    {
        std::stringstream ret;
        if(!m_sender.empty())  ret << ":" << m_sender << " ";
        if(!m_command.empty()) ret << m_command << " ";
        if(!m_params.empty())  ret << m_params << " ";
        if(!m_data.empty())    ret << ":" << m_data;
        if(!ret.str().empty()) ret << "\r\n";
        
        return ret.str();
    }

    std::ostream &operator<<(std::ostream &os, IRCMessage const &rhs)
    {
        os << "Sender: "  << rhs.sender()  << std::endl
           << "Command: " << rhs.command() << std::endl
           << "Params: "  << rhs.params()  << std::endl
           << "Data: "    << rhs.data();
        return os;
    }
}}