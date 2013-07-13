//
//  ChatterBot.hpp
//  PandoraBotIRC
//
//  Created by Stephen Hall on 6/29/13.
//  Copyright (c) 2013 Stephen Hall. All rights reserved.
//

#ifndef PandoraBotIRC_ChatterBot_hpp
#define PandoraBotIRC_ChatterBot_hpp
#include <string>

namespace pbirc { namespace cb {

/*
 * Abstract base class representing a chatterbot.
 */
class ChatterBot
{
public:
    ChatterBot() = default;
    virtual ~ChatterBot() = default;
    
    virtual std::string think(std::string const &msg) = 0;
};
    
}}
#endif
