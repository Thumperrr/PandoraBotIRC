//
// main.cpp
// PandoraBotIRC
//
// Created by Stephen Hall on 7/12/13.
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

#include "irc/PandoraIRCBot.hpp"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <string>

/**
 * @namespace pbirc
 * @brief Namespace for the PandoraBotIRC project.
 *
 * @namespace pbirc::util
 * @brief Namespace for general utility functions
 *
 * @namespace pbirc::irc
 * @brief Namespace for everything to do with irc connections
 *
 * @namespace pbirc::cb
 * @brief Namespace for everything to do with chatter bots
 */

void printUsage(std::ostream &os)
{
    os << "Usage: <server> <port> <nick> <channel>." << std::endl;
    os << "\tAll fields are required." << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc < 5)
    {
        std::cout << "Error: Invalid number of parameters" << std::endl;
        printUsage(std::cout);
        return -1;
    }

    //!< [PandoraIRCBot usage]
    pbirc::irc::PandoraIRCBot bot(argv[1],
                                  boost::lexical_cast<int>(argv[2]), 
                                  argv[3], 
                                  "#" + std::string(argv[4]));

    return bot.run();
    //!< [PandoraIRCBot usage]
}