/**
 *
 */

#ifndef __CPPS_PARSE_H_INCLUDED__
#define __CPPS_PARSE_H_INCLUDED__

#include "Token.h"
#include "Scope.h"

namespace cpps
{

extern void parse( const Token::List& tokens, Scope& scope );

} // end namespace cpps

#endif // __CPPS_PARSE_H_INCLUDED__

