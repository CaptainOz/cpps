/**
 * @file
 *
 * @brief Contains the code for the Scope class.
 *
 * @author Nate Lillich
 */


#include "Scope.h"

using namespace std;

namespace cpps
{

Scope::Scope( void )
{
}


/******************************************************************************/


Object Scope::exec(
        const    string& code,
        unsigned int     lineNumber
    )
{
    // Tokenize
    Token::List* tokens = Token::tokenize( code );

    // Parse
    ParseTree* statements = _parse( *tokens );

    // Execute
    // Convert RPN into op-code where needed
    // Replace constant expressions with their values
}


/******************************************************************************/


ParseTree* Scope::_parse( const Token::List& tokens )
{
    // Convert tokens into RPN stack.
    for( Token::List::const_iterator it = tokens.begin();
         it != tokens.end();
         ++it )
    {
        
    }

    // Create function and block structures as encountered
}


} // end namespace cpps

