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
    const Token& token = m_tokenizer->getNextToken();
    const Token::Type& type = token.getType();

    if( type == Token::EndOfFile )
        return 0;

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
    if( m_tokenizer )
        delete m_tokenizer;
    m_tokenizer = new Tokenizer( code );
    parse();
}

} // end namespace cpps

