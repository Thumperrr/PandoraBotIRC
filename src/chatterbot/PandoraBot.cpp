//
//  PandoraBot.cpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 6/29/13.
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

#include "PandoraBot.hpp"
#include "util/Utility.hpp"

#include <SFML/Network.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

#include <string>

namespace pbirc { namespace cb {
    
    PandoraBot::PandoraBot(std::string const &botid)
    : m_botid(botid)
    , m_custid(boost::lexical_cast<std::string>(boost::uuids::random_generator()()))
    {
    }
    
    std::string PandoraBot::think(std::string const &msg)
    {
        sf::Http session("http://www.pandorabots.com");
        sf::Http::Request req("pandora/talk-xml?botid="+m_botid
                             , sf::Http::Request::Method::Post );
        
        std::stringstream body;
        body << "custid=" << m_custid << "&input=" << util::URLEncode(msg);
        req.setBody(body.str());

        return process_input(session.sendRequest(req).getBody());
    }

    std::string PandoraBot::process_input(std::string const &s)
    {
        //Relevant body text is in between <that> tags.
        std::size_t first = s.find("<that>");
        std::string relevantText = 
                first != std::string::npos
                ? s.substr(first, s.find("</that>")-first)
                : s;

        //save some typing
        using namespace pbirc::util;
        return removeLeadingSpaces(stripHtml(HTMLUnEscape(relevantText)));
    }
    
}}
