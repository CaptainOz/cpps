/**
 * @file
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_TOKENIZER_H_INCLUDED__
#define __CPPS_TOKENIZER_H_INCLUDED__

#include <string>

#include "Scriptable.h"
#include "Token.h"

namespace cpps
{

class Tokenizer
{
public:
    //! Code constructor
    /**
     * @param code The code string to tokenize.
     */
    Tokenizer( const std::string& code );

    //! Empty ~destructor.
    ~Tokenizer( void ) {}

    //! Gets the next token from the code stream.
    /**
     * @return The extracted token.
     */
    Token getNextToken( void );

private:
    const std::string   m_code;
    const unsigned int& m_length;
          unsigned int  m_lineCounter;
          unsigned int  m_pos;


    //! Detects if the @p code at the given @p position matches the @p keyword.
    /**
     * This is different from Token::_matchToken in that it does an additional
     * check that the character following the keyword is not alphanumeric or an
     * underscore.
     *
     * @param keyword The keyword to compare it to.
     *
     * @return True if the following code chunk is the given keyword.
     */
    bool _matchKeyword( const char* keyword ) const throw();

    //! Detects if the @p code at the given @p position matches the @p token.
    /**
     * @param token The token to compare it to.
     *
     * @return True if the following code chunk is the given token.
     */
    bool _matchToken( const char* token ) const throw();

    //! Extracts a quoted string.
    /**
     * @throws ParseException if a newline or end of file is encountered before
     *         the end of the line.
     *
     * @return The extracted string literal token.
     */
    Token _extractString( void ) throw( ParseException );

    //! Extracts a number.
    /**
     * @throws ParseException if the number contains illegal characters.
     *
     * @return The extracted numeric literal token.
     */
    Token _extractNumber( void ) throw( ParseException );

    //! Extracts an identifier for a variable or typename.
    /**
     * @throws ParseException if the identifier contains illegal characters.
     *
     * @return The extracted identifier token.
     */
    Token _extractIdentifier( void ) throw( ParseException );

    //! Extracts a single-line comment.
    void _extractCommentLine( void ) throw();

    //! Extracts a block comment.
    /**
     * @throws ParseException if the comment block is not closed.
     */
    void _extractCommentBlock( void ) throw( ParseException );

    //! Extracts the given keyword.
    /**
     * @param keywordIndex The index of the keyword from the Token::_keywords
     *                     array to extract.
     *
     * @return The extracted keyword token.
     */
    Token _extractKeyword( const int& keywordIndex ) throw();

    //! Extracts the given operator.
    /**
     * @param operatorIndex The index of the keyword from the Token::_operators
     *                      array to extract.
     *
     * @return The extracted keyword token.
     */
    Token _extractOperator( const int& operatorIndex ) throw();
}; // end class Tokenizer


/*****************************************************************************/


inline Tokenizer::Tokenizer( const std::string& code )
    : m_code( code ),
      m_length( m_code.size() ),
      m_lineCounter( 1 ),
      m_pos( 0 )
{
}


} // end namespace cpps

#endif // __CPPS_TOKENIZER_H_INCLUDED__
