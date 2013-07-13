#include "Utility.hpp"

namespace pbirc { namespace util { 

	bool isReserved(char const &c)
    {
        return !(isalnum(c) || c == '-' || c == '.' || c == '_' || c == '~');
    }

    std::string URLEncode(std::string const &s)
    {
        std::stringstream ret;
        ret << std::setbase(16);
        
        for(auto &i: s)
        {
            if(isReserved(i)) ret << '%' << (int)i;
            else ret << i;
        }
        return ret.str();
    }

    std::string HTMLEscape(std::string s)
    {
        using boost::algorithm::replace_all;
        replace_all(s, "&",  "&amp;");
        replace_all(s, "\"", "&quot;");
        replace_all(s, "\'", "&apos;");
        replace_all(s, "<",  "&lt;");
        replace_all(s, ">",  "&gt;");
        replace_all(s, " ",  "&nbsp;");
        return s;
    }

    std::string HTMLUnEscape(std::string s)
    {
        using boost::algorithm::replace_all;
        replace_all(s, "&amp;",  "&");
        replace_all(s, "&quot;", "\"");
        replace_all(s, "&apos;", "\'");
        replace_all(s, "&lt;",   "<");
        replace_all(s, "&gt;",   ">");
        replace_all(s, "&nbsp;", " ");
        replace_all(s, "<br>",   "\n");
        return s;
    }

    std::string stripHtml(std::string const &s)
    {
        static const std::regex expr("<(.*?)>");
        return std::regex_replace(s, expr, "");
    }

    template<typename ReverseIter>
    typename ReverseIter::iterator_type make_forward(ReverseIter i)
    {
        return --i.base();
    }

    std::string removeLeadingSpaces(std::string const &s)
    {
        return std::string(std::find_if(s.begin(), s.end(), [](char const &c)->bool{return !isspace(c);}), s.end());
    }

    std::string removeTrailingSpaces(std::string const &s)
    {
        return std::string(s.begin(), ++make_forward(std::find_if(s.rbegin(), s.rend(), [](char const &c)->bool{return !isspace(c);})));
    }

}}