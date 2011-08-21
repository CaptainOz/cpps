/**
 *
 */

#include <cstdlib>

#include "Parser.ih"

using namespace std;

namespace cpps
{
typedef AbstractSyntaxTree AST;

int Parser::lex( void )
{
    const Token& token = m_tokenizer->getNextToken();

    if( token.is( Token::EndOfFile ) )
        return 0;

    if( token.is( Token::NumericLiteral ) )
        d_val__ = new nodes::NumericLiteral(
                strtod( token.getString().c_str(), NULL )
            );

    return token.getParserType();
}

void Parser::exec( const string& code )
{
    if( m_tokenizer )
        delete m_tokenizer;
    m_tokenizer = new Tokenizer( code );
    parse();
}

} // end namespace cpps

