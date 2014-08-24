// ----------------------------------------------------------------------------
// Copyright (C) 2002-2007 Marcin Kalicinski
// Copyright (C) 2007 Alexey Baskakov
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_WRITER_SETTINGS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_WRITER_SETTINGS_HPP_INCLUDED

#include <string>
#include <boost/property_tree/detail/ptree_utils.hpp>

namespace boost { namespace property_tree { namespace xml_parser
{
    
    // Naively convert narrow string to another character type
    template<class Str>
    Str widen(const char *text)
    {
	typedef typename Str::value_type Ch;
        Str result;
        while (*text)
        {
            result += Ch(*text);
            ++text;
        }
        return result;
    }

    //! Xml writer settings. The default settings lead to no pretty printing.
    template<class Str>
    class xml_writer_settings
    {
	typedef typename Str::value_type Ch;
    public:
        xml_writer_settings(Ch inchar = Ch(' '),
                typename Str::size_type incount = 0,
                const Str &enc = widen<Str>("utf-8"))
            : indent_char(inchar)
            , indent_count(incount)
            , encoding(enc)
        {
        }

        Ch indent_char;
        typename Str::size_type indent_count;
        Str encoding;
    };

    template<>
    class xml_writer_settings<char>
    {
    public:
        xml_writer_settings(char inchar = ' ',
                std::string::size_type incount = 0,
                const std::string &enc = widen<std::string>("utf-8"))
            : indent_char(inchar)
            , indent_count(incount)
            , encoding(enc)
        {
        }

        char indent_char;
        std::string::size_type indent_count;
        std::string encoding;
    };

    template <class Str>
    xml_writer_settings<Str> xml_writer_make_settings(typename Str::value_type indent_char = (typename Str::value_type)(' '),
        typename Str::size_type indent_count = 0,
        const Str &encoding = widen<Str>("utf-8"))
    {
        return xml_writer_settings<Str>(indent_char, indent_count, encoding);
    }

    template <class size_type>
    xml_writer_settings<std::string> xml_writer_make_settings(char indent_char,
        size_type indent_count)
    {
        return xml_writer_settings<std::string>(indent_char, indent_count, widen<std::string>("utf-8"));
    }

} } }

#endif
