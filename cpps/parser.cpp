/**
 *
 */

#include <cstdlib>

#include "Parser.ih"

using namespace std;
using namespace cpps;

int Parser::lex( void )
{
    static int mvr = 0;

    if( mvr >= tokens->size() )
        return 0;

    const Token* token = tokens->at(mvr++);
    const Token::Type& type = token->getType();

    if( type == Token::Semicolon )
        return ';';

    if( type == Token::Plus )
        return '+';

    if( type == Token::NumericLiteral )
        d_val__ = strtod( token->getString().c_str(), NULL );

    return type;
}

int Parser::exec( const string& code )
{
    tokens = Token::tokenize( code );
    it = tokens->begin();
    return parse();
}

