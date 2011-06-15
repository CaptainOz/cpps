/**
 * @file
 *
 * @brief Contains the code for the Scope class.
 *
 * @author Nate Lillich
 */


#include "Scope.h"
#include <sstream>

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


} // end namespace cpps

