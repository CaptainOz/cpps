/**
 * @file
 *
 * @author Nate Lillich
 */

#include "Tokenizer.h"

namespace cpps
{

Token Tokenizer::getNextToken( void ) throw( ParseException )
{
    for( char thisC; m_codeStream && m_codeStream.get(thisC); )
    {
        // Skip whitespace.
        if( isspace( thisC ) )
        {
            if( thisC == '\n' )
                ++m_lineCounter;
            continue;
        }

        // Set up the additional variables we'll need.
        const char& nextC = (char)m_codeStream.peek();

        // Are we starting a string literal? (StringLiteral)
        if( thisC == '\'' || thisC == '"' )
             return _extractString();

        // Or is this a numeric literal? (NumericLiteral)
        else if( isdigit( thisC ) )
            return _extractNumber();

        // Or is this a variable identifier? (Identifier)
        else if( thisC == '$' )
            return Token::_extractIdentifier();

        // Or is this a one-line comment? (CommentLine)
        else if( thisC == '/' && nextC == '/' )
        {
            _extractCommentLine();
            continue;
        }

        // Or is this a comment block? (CommentBlock)
        else if( thisC == '/' && nextC == '*' )
        {
            _extractCommentBlock();
            continue;
        }

        // Next lets check for a keyword
        for( const char** mvr = Token::_keywords; *mvr; ++mvr )
            if( _matchKeyword( *mvr ) )
                return _extractKeyword( mvr - Token::_keywords );

        // Next lets check for an operator.
        for( const char** mvr = Token::_operators; *mvr; ++mvr )
            if( _matchToken( *mvr ) )
                return _extractOperator( mvr - Token::_operators );

        // If we still haven't tokenized the string yet, lets see if its a
        // typename (i.e. class name, function name, etc).
        if( isalpha( thisC ) || thisC == '_' )
            return _extractIdentifier();

        // Still haven't tokenized it!? Must be an error.
        throw ParseException(
                ParseException::UnknownToken,   // Exception type
                m_codeStream.str(),             // Erroneous code string
                m_codeStream.tellg(),           // Position in string
                m_lineCounter,                  // Line number of error
                "Unrecognized token."
            );
    }
}


} // end namespace cpps
