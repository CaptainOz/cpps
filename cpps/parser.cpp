/**
 *
 */

#include <cstdlib>

#include "Parser.ih"

using namespace std;

namespace cpps
{

int Parser::lex( void )
{
    if( it == tokens.end() )
        return 0;

    const Token& token = *(it++);
    const Token::Type& type = token.getType();

    if( token.isOperator() )
        return token.getString().at(0);

    if( type == Token::NumericLiteral )
    {
        d_val__ = new Number( strtod( token.getString().c_str(), NULL ) );
        return Parser::NUM;
    }

    return type;
}

void Parser::exec( const string& code )
{
    Token::tokenize( code, tokens );
    it = tokens.begin();
    parse();
}

} // end namespace cpps

