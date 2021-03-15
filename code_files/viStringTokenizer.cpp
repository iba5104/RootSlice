/***************************************************************
 * Name:      viStringTokenizer.cpp
 * Purpose:   The implementation of class viStringTokenizer
 * Author:    Bangyou Zheng (byzheng@cau.edu.cn)
 * Created:   01/02/2009
 * Copyright: Bangyou Zheng (http://www.viscs.org)
 * License:   GPL
 * Notes:
 *
 * $Revision: 665 $
 * $Id: viStringTokenizer.cpp 665 2009-12-11 07:53:20Z byzheng $
 * $Date: 2009-12-11 17:53:20 +1000 (Fri, 11 Dec 2009) $
 * $LastChangedBy: byzheng $
 * $HeadURL: http://svn.viscs.org/svn/zplant/trunk/viLibrary/src/viStringTokenizer.cpp $
 **************************************************************/
#include "viStringTokenizer.h"
#include <stdlib.h>
//-----------------------------------------------------------------------------
viStringTokenizer::~viStringTokenizer()
{
    //dtor
}
//-----------------------------------------------------------------------------
viStringTokenizer::viStringTokenizer( const string& str,
                                      const string& delims,
                                      viStringTokenizerMode mode)
{
    SetString(str, delims, mode);
}
//-----------------------------------------------------------------------------
viStringTokenizer::viStringTokenizer( const char * str,
                                      const char * delims,
                                      viStringTokenizerMode mode)
{
    string strs = str;
    string delimss =delims;
    SetString(strs, delimss, mode);
}
//-----------------------------------------------------------------------------
void viStringTokenizer::SetString(const string& str,
                                  const string& delims,
                                  viStringTokenizerMode mode)
{
    if ( mode == viTOKEN_DEFAULT )
    {
        // by default, we behave like strtok() if the delimiters are only
        // whitespace characters and as viTOKEN_RET_EMPTY otherwise (for
        // whitespace delimiters, strtok() behaviour is better because we want
        // to count consecutive spaces as one delimiter)
        const char *p;
        for ( p = delims.c_str(); *p; p++ )
        {
            if ( p !=" " )
                break;
        }

        if ( *p )
        {
            // not whitespace char in delims
            mode = viTOKEN_RET_EMPTY;
        }
        else
        {
            // only whitespaces
            mode = viTOKEN_STRTOK;
        }
    }

    m_delims = delims;
    m_mode = mode;

    Reinit(str);
}
//-----------------------------------------------------------------------------
void viStringTokenizer::Reinit(const string& str)
{
    m_string = str;
    m_pos = 0;
    m_lastDelim ='\0';
}
//-----------------------------------------------------------------------------
void viStringTokenizer::Reinit(const char * str)
{
    string strs = str;
    Reinit(str);
}
//-----------------------------------------------------------------------------
// do we have more of them?
bool viStringTokenizer::HasMoreTokens() const
{
    if ( m_string.find_first_not_of(m_delims, m_pos) != string::npos )
    {
        // there are non delimiter characters left, so we do have more tokens
        return true;
    }

    switch ( m_mode )
    {
    case viTOKEN_RET_EMPTY:
    case viTOKEN_RET_DELIMS:
        // special hack for wxTOKEN_RET_EMPTY: we should return the initial
        // empty token even if there are only delimiters after it
        return m_pos == 0 && !m_string.empty();

    case viTOKEN_RET_EMPTY_ALL:
        // special hack for wxTOKEN_RET_EMPTY_ALL: we can know if we had
        // already returned the trailing empty token after the last
        // delimiter by examining m_lastDelim: it is set to NUL if we run
        // up to the end of the string in GetNextToken(), but if it is not
        // NUL yet we still have this last token to return even if m_pos is
        // already at m_string.length()
        return m_pos < m_string.length() || m_lastDelim != '\0';

    case viTOKEN_INVALID:
    case viTOKEN_DEFAULT:
    case viTOKEN_STRTOK:
        // never return empty delimiters
        break;
    }

    return false;
}
//-----------------------------------------------------------------------------
string viStringTokenizer::GetNextToken()
{
    string token;
    do
    {
        if ( !HasMoreTokens() )
        {
            break;
        }

        // find the end of this token
        size_t pos = m_string.find_first_of(m_delims, m_pos);

        // and the start of the next one
        if ( pos == string::npos )
        {
            // no more delimiters, the token is everything till the end of
            // string
            token.assign(m_string, m_pos, string::npos);

            // skip the token
            m_pos = m_string.length();

            // it wasn't terminated
            m_lastDelim = '\0';
        }
        else // we found a delimiter at pos
        {
            // in wxTOKEN_RET_DELIMS mode we return the delimiter character
            // with token, otherwise leave it out
            size_t len = pos - m_pos;
            if ( m_mode == viTOKEN_RET_DELIMS )
                len++;

            token.assign(m_string, m_pos, len);

            // skip the token and the trailing delimiter
            m_pos = pos + 1;

            m_lastDelim = m_string[pos];
        }
    }
    while ( !AllowEmpty() && token.empty() );

    return token;
}
//-----------------------------------------------------------------------------
float viStringTokenizer::GetNextTokenFloat()
{
    string token = GetNextToken();
    return atof(token.c_str());
}
//-----------------------------------------------------------------------------
int viStringTokenizer::GetNextTokenInt()
{
    string token = GetNextToken();
    return atoi(token.c_str());
}
//-----------------------------------------------------------------------------
const char * viStringTokenizer::GetNextTokenChar()
{
    string token = GetNextToken();
    return token.c_str();
}
//-----------------------------------------------------------------------------
size_t viStringTokenizer::RemainTokensCount() const
{
    return TokensCount(m_pos);
}
//-----------------------------------------------------------------------------
size_t viStringTokenizer::TotalTokensCount() const
{
    return TokensCount(0);
}
//-----------------------------------------------------------------------------
size_t viStringTokenizer::TokensCount(size_t pos) const
{
    // VZ: this function is IMHO not very useful, so it's probably not very
    //     important if its implementation here is not as efficient as it
    //     could be -- but OTOH like this we're sure to get the correct answer
    //     in all modes
    viStringTokenizer tkz(m_string.c_str() + pos, m_delims, m_mode);

    size_t count = 0;
    while ( tkz.HasMoreTokens() )
    {
        count++;

        (void)tkz.GetNextToken();
    }

    return count;
}

