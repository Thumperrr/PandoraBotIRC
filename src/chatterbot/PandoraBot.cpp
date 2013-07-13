//
//  PandoraBot.cpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 6/29/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

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
