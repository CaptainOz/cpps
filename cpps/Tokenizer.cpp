/**
 * @file
 *
 * @author Nate Lillich
 */

#include "Tokenizer.h"

using namespace std;

namespace cpps
{

Token Tokenizer::getNextToken( void ) throw( ParseException )
{
    for( char thisC = m_code[ m_pos ];
         m_pos < m_length;
         thisC = m_code[ ++m_pos ] )
    {
        // Skip whitespace.
        if( isspace( thisC ) )
        {
            if( thisC == '\n' )
                ++m_lineCounter;
            continue;
        }

        // Set up the additional variables we'll need.
        const char& nextC = m_pos+1 < m_length ? m_code[ m_pos+1 ] : -1;

        // Are we starting a string literal? (StringLiteral)
        if( thisC == '\'' || thisC == '"' )
             return _extractString();

        // Or is this a numeric literal? (NumericLiteral)
        else if( isdigit( thisC ) )
            return _extractNumber();

        // Or is this a variable identifier? (Identifier)
        else if( thisC == '$' )
            return _extractIdentifier();

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
                m_code,                         // Erroneous code string
                m_pos,                          // Position in string
                m_lineCounter,                  // Line number of error
                "Unrecognized token."
            );
    }
}


/******************************************************************************/


bool Tokenizer::_matchKeyword( const char* keyword ) const throw()
{
    // Does the token match the keyword?
    if( !_matchToken( keyword ) )
        return false;

    // The string matches the keyword, but is it the whole word? It could be the
    // start of another (i.e. newFooBar).
    const char&   charAfter = m_code[ m_pos + strlen(keyword) ];
    return !isalnum( charAfter ) && // char after is not alphanumeric
            charAfter != '_';       // char after is not underscore
}


/******************************************************************************/


bool Tokenizer::_matchToken( const char* token ) const throw()
{
    // Loop through the string to find a non-matching character.
    int i;
    for( i = 0; token[i] && m_pos+i < m_length; ++i )
        if( m_code[ m_pos+i ] != token[i] )
            return false;

    // We didn't find a non-matching character, but did we get through the whole
    // token? (remaining code could be shorter than token length.)
    return token[i] == 0;
}


/******************************************************************************/


Token Tokenizer::_extractString( void ) throw( ParseException )
{
    // Loop through the string pulling out each character until we find the
    // closing quote.
    string tokenStr;
    const char& quoteChar = m_code[ m_pos ];
    for( char c = m_code[ ++m_pos ];
         c != quoteChar;
         tokenStr += c, c = m_code[ ++m_pos ] )
    {
        // If this char is the escape character, skip it.
        if( c == '\\' )
            ++m_pos;

        // Check that we are still within range and the line hasn't ended.
        if( m_pos >= m_length || c == '\n' )
            throw ParseException(
                    ParseException::UnexpectedToken,
                    m_code,
                    m_pos,
                    m_lineCounter,
                    "Unclosed string literal."
                );
    }

    // Create and return a new token.
    return Token( Token::StringLiteral, m_lineCounter, tokenStr );
}


/******************************************************************************/


Token Tokenizer::_extractNumber( void ) throw( ParseException )
{
    enum NumberBase {
        nb_Binary,
        nb_Octal,
        nb_Decimal,
        nb_Hex
    };

    // First lets figure out what kind of digit string this is. This will be
    // used further down while extracting to ensure valid characters.
    int type;
    const char& nextC = m_code[m_pos+1];
    string tokenStr;
    if( m_code[m_pos] != '0' || nextC == '.' )
        type = nb_Decimal;
    else if( nextC == 'b' || nextC == 'B' )
    {
        type = nb_Binary;
        tokenStr += "0b";
        m_pos += 2;
    }
    else if( nextC == 'x' || nextC == 'X' )
    {
        type = nb_Hex;
        tokenStr += "0x";
        m_pos += 2;
    }
    else
        type = nb_Octal;

    // Extract all the digits
    bool decimalIncluded = false;
    for( char c = tolower(m_code[m_pos]);
         m_pos < m_length       &&
        (isdigit(c)             ||
         c == '.'               ||
         (c <= 'f' && c >= 'a')  );
         tokenStr += c,
         c = tolower(m_code[++m_pos]) )
    {
        // Check for scientific notation, which is only valid in decimal mode.
        if( type == nb_Decimal && c == 'e' )
        {
            // The next character must be a '+' or '-'
            const char& nextC = m_pos+1 < m_length ? m_code[++m_pos] : 0;
            if( nextC != '-' && nextC != '+' )
                throw ParseException(
                        ParseException::UnexpectedToken,
                        m_code,
                        m_pos,
                        m_lineCounter,
                        "Expected one of '+' or '-'."
                    );

            // Append the 'e' to the token string and move on.
            tokenStr += c;
            c = nextC;
            continue;
        }

        // Check that this character is valid in a number.
        if( (c == '.' && type != nb_Decimal)            || // Only decimal has decimal points
            (c != '.' && !isdigit(c) && type != nb_Hex) || // Only hex has non-digit chars
            (c >  '7' && type == nb_Octal)              || // Octal must be between 0 and 7
            (c >  '1' && type == nb_Binary)              ) // Binary must be 0 or 1
            throw ParseException(
                    ParseException::UnexpectedToken,
                    m_code,
                    m_pos,
                    m_lineCounter,
                    "Invalid character in numeric literal."
                );

        // If we've come across another decimal place and we've already included
        // a decimal place, break the loop here.
        if( decimalIncluded && c == '.' )
            break;
        else if( c == '.' )
            decimalIncluded = true;
    }

    // Create and return a new token.
    --m_pos;
    return Token( Token::NumericLiteral, m_lineCounter, tokenStr );
}


/******************************************************************************/


Token Tokenizer::_extractIdentifier( void ) throw( ParseException )
{
    // What type of identifier are we extracting?
    Token::Type tokenType;
    if( m_code[m_pos] == '$' )
    {
        tokenType = Token::Variable;
        ++m_pos;
    }
    else
        tokenType = Token::TypeName;

    // Check that the first character after the $ is valid.
    if( !isalpha( m_code[m_pos] ) && m_code[m_pos] != '_' )
        throw ParseException(
                ParseException::InvalidName,
                m_code,
                m_pos,
                m_lineCounter,
                "Variable names must start with an alphabetic character."
            );

    // Now extract the identifier's name
    string tokenStr;
    for( char c = m_code[ m_pos ];
         m_pos < m_length && (isalnum( c ) || c == '_');
         c = m_code[ ++m_pos ] )
        tokenStr += c;

    // Create and return a new token.
    return Token( tokenType, m_lineCounter, tokenStr );
}


/******************************************************************************/


void Tokenizer::_extractCommentLine( void ) throw()
{
    // Comment lines end at the new-line.
    while( ++m_pos < m_length && m_code[ m_pos ] != '\n' )
    {}  // Do nothing in the loop
}


/******************************************************************************/


void Tokenizer::_extractCommentBlock( void ) throw( ParseException )
{
    for( m_pos += 2; m_code[ m_pos ] != '*' && m_code[ m_pos+1 ] != '/'; ++m_pos )
    {
        // Make sure we haven't reached the end of the code before the comment
        // was closed.
        if( m_pos >= m_length )
            throw ParseException(
                    ParseException::UnexpectedToken,
                    m_code,
                    m_pos,
                    m_lineCounter,
                    "Unclosed block comment."
                );

        // Be sure to count up the lines within the comment
        if( m_code[ m_pos ] == '\n' )
            ++m_lineCounter;
    }
    ++m_pos;    // Skip the closing '/'
}


/******************************************************************************/


Token Tokenizer::_extractKeyword( const int& keywordIndex ) throw()
{
    // Calculate the token type and move the position up
    const Token::Type tokenType = (Token::Type)((int)Token::Break + keywordIndex);
    m_pos += strlen( Token::_keywords[ keywordIndex ] ) - 1;
    return Token( tokenType, m_lineCounter );
}


/******************************************************************************/


Token Tokenizer::_extractOperator( const int& operatorIndex ) throw()
{
    // Calculate the token type and move the position up
    const Token::Type tokenType = (Token::Type)((int)Token::Scope + operatorIndex);
    m_pos += strlen( Token::_operators[ operatorIndex ] ) - 1;
    return Token( tokenType, m_lineCounter );
}


} // end namespace cpps
