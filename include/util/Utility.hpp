//
//  Utility.hpp
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

#ifndef PandoraBotIRC_Utility_hpp
#define PandoraBotIRC_Utility_hpp

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#include <sstream>
#include <iomanip>
#include <string>

namespace pbirc { namespace util {
    
    /**
     * Function checks a character to see if a character is reserved in URLs. 
     * A reserved character is used for a special purpose in URLs.
     *
     * @param[in] c character to be tested.
     * @return returns true if a character is URL reserved. Otherwise false.
     */
    bool isReserved(char const &c);
    
    /**
     * URL encodes a string -- Removes reserved characters and replaces them with hex counterparts. 
     * "The quick brown fox" will become "The%20quick%20brown%20fox"
     *
     * @param[in] s string to encode
     * @return encoded version of string
     */
    std::string URLEncode(std::string const &s);
    
    /**
     * Replaces escape characters in HTML with their proper counterparts.
     *
     * @param[in] s string to escape
     * @return the escaped string
     */
    std::string HTMLEscape(std::string s);
    
    /**
     * Does the opposite of HTMLEscape
     *
     * @param[in] s the string to unescape
     * @return the unescaped string
     */
    std::string HTMLUnEscape(std::string s);
    
    /**
     * Removes all HTML tags from a string.
     *
     * @param[in] s string to strip html from
     * @return html-free string
     */
    std::string stripHtml(std::string const &s);
    
    /**
     * Helper function to convert a reverse_iterator into a forward_iterator
     *
     * @param[in] i reverse_iterator to be made forward
     * @return forward_iterator that points to the same object as i. 
     */
    template<typename ReverseIter>
    typename ReverseIter::iterator_type make_forward(ReverseIter i);
    
    /**
     * Removes the leading spaces from a string
     *
     * @param[in] s string to remove whitespaces from
     * @return string with no leading whitespaces
     */
    std::string removeLeadingSpaces(std::string const &s);
    /**
     * Removes the trailing whitespaces from a string
     *
     * @param[in] s string to remove trailing whitespaces from
     * @return string with no trailing whitespaces
     */
    std::string removeTrailingSpaces(std::string const &s);
}}

#endif
