/***************************************************************
 * Name:      viStringTokenizer.h
 * Purpose:   String tokenizer
 * Author:    Bangyou Zheng (byzheng@cau.edu.cn)
 * Created:   08/28/2008
 * Copyright: Bangyou Zheng (http://www.viscs.org)
 * License:   GPL
 * Notes:     This class is derived from class wxStringTokenizer,
              but rewrote for std::string
 *
 * $Revision: 665 $
 * $Id: viStringTokenizer.h 665 2009-12-11 07:53:20Z byzheng $
 * $Date: 2009-12-11 17:53:20 +1000 (Fri, 11 Dec 2009) $
 * $LastChangedBy: byzheng $
 * $HeadURL: http://svn.viscs.org/svn/zplant/trunk/viLibrary/include/viStringTokenizer.h $
 **************************************************************/

#ifndef VISTRINGTOKENIZER_H
#define VISTRINGTOKENIZER_H

#include <string>
using namespace std;

/// default: delimiters are usual white space characters
#define viDEFAULT_DELIMITERS ", \t\r\n"

/// wxStringTokenizer mode flags which determine its behaviour
enum viStringTokenizerMode
{
    viTOKEN_INVALID = -1,   ///< set by def ctor until SetString() is called
    viTOKEN_DEFAULT,        ///< strtok() for whitespace delims, RET_EMPTY else
    viTOKEN_RET_EMPTY,      ///< return empty token in the middle of the string
    viTOKEN_RET_EMPTY_ALL,  ///< return trailing empty tokens too
    viTOKEN_RET_DELIMS,     ///< return the delim with token (implies RET_EMPTY)
    viTOKEN_STRTOK          ///< behave exactly like strtok(3)
};
/// viStringTokenizer split a string into a number of token according delimiters.
/**
 * viStringTokenizer derived from wxStringTokenizer (http://www.wxwidgets.org).
 * It rewrote for stl string and also added some functions.
 */
class viStringTokenizer
{
public:
    /// Default constructor
    viStringTokenizer()
    {
        m_mode = viTOKEN_INVALID;
    }
    /// ctor which gives us "the string"
    viStringTokenizer( const string& str,
                       const string& delims = viDEFAULT_DELIMITERS,
                       viStringTokenizerMode mode = viTOKEN_DEFAULT);
    /// ctor which gives us the "const char *"
    viStringTokenizer( const char * str,
                       const char * delims = viDEFAULT_DELIMITERS,
                       viStringTokenizerMode mode = viTOKEN_DEFAULT);
    /// Default destructor
    virtual ~viStringTokenizer();
    /// args are same as for the non default ctor above
    void SetString( const string& str,
                    const string& delims = viDEFAULT_DELIMITERS,
                    viStringTokenizerMode mode = viTOKEN_DEFAULT);
    /// get current tokenizer state
    /**
     * returns the part of the string which remains to tokenize (*not* the
     * initial string)
     */
    string GetRemainString() const
    {
        return m_string.substr(m_pos);
    }
    /// get tokenizer string
    string GetString() const
    {
        return m_string;
    }
    /// did we reach the end of the string?
    bool HasMoreTokens() const;
    /// get the next token, will return empty string if !HasMoreTokens()
    string GetNextToken();
    /// get the next "float" token, will return empty string if !HasMoreTokens()
    float GetNextTokenFloat();
    /// get the next "Int" token, will return empty string if !HasMoreTokens()
    int GetNextTokenInt();
    /// get the next "Const char *" token, will return empty string if !HasMoreTokens()
    const char * GetNextTokenChar();
    /// tokens access, return the number of remaining tokens
    size_t RemainTokensCount() const;
    /// tokens access, return the number of total tokens
    size_t TotalTokensCount() const;
    /// do we return empty tokens?
    bool AllowEmpty() const
    {
        return m_mode != viTOKEN_STRTOK;
    }
    /// reinitialize the tokenizer with the same delimiters/mode
    void Reinit(const string& str);
    void Reinit(const char * str);
protected:
    bool IsOk() const
    {
        return m_mode != viTOKEN_INVALID;
    }
    string m_string,                ///< the string we tokenize
    m_delims;                ///< all possible delimiters
    size_t   m_pos;                 ///< the current position in m_string
    viStringTokenizerMode m_mode;   ///< see wxTOKEN_XXX values
    char    m_lastDelim;            ///< delimiter after last token or '\0'
private:
    size_t TokensCount(size_t pos) const;
};

#endif // VISTRINGTOKENIZER_H
