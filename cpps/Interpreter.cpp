/**
 * @file Interpreter.cpp
 *
 * @brief Contains the code for the CPPS Interpreter.
 *
 * @author Nate Lillich
 */


#include "Interpreter.h"
#include <sstream>

using namespace std;

namespace cpps
{

Interpreter::Interpreter( void )
{
}


/*********************************************************/


Object Interpreter::exec(
        const    string& code,
                 Scope&  scope,
        unsigned int     lineNumber
    )
{
    // Tokenize
    Token::List tokens = Token::tokenize( code );
    

    // Parse / Execute
}


} // end namespace cpps

