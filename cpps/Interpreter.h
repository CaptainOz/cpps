/**
 * @file Interpreter.h
 *
 * @brief Describes the CPPS interpreter class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_INTERPRETER_H_INCLUDED__
#define __CPPS_INTERPRETER_H_INCLUDED__

#include <string>

#include "Object.h"

namespace cpps
{

class Interpreter
{
private:

public:
    Interpreter( void );
    
    Object exec( const std::string& code, Scope& scope, unsigned int lineNumber = 0 );

}; // end class Interpreter#include "Object.h"


} // end namespace cpps

#endif // __CPPS_INTERPRETER_H_INCLUDED__

