/**
 *
 */


#include "Exceptions.h"

using namespace std;

namespace cpps
{

ParseException::ParseException(
        const ParseException::Type& exceptionType,
        const string&       code,
        const          int& offset,
        const unsigned int& lineNumber,
        const string&       message
    ) throw()
    : mType( exceptionType ),
      mMessage( message ),
      mLineNumber( lineNumber )
{
    // Find the previous newline
    int start;
    for( start = offset - 1; start > 0 && code[ start ] != '\n'; --start )
        ; // Do nothing in loop.

    // Find the next newline
    int end;
    for( end = offset; end < code.size() && code[ end ] != '\n'; ++end )
        ; // Do nothing in loop.

    // Take the substring between them and get the offset from the substr.
    mCodeLine = code.substr( start, end );
    mOffset = offset - start;
}


/******************************************************************************/


RuntimeException::RuntimeException(
        const RuntimeException::Type& exceptionType,
        const unsigned int& lineNumber,
        const std::string&  message
    ) throw()
    : m_type( exceptionType ),
      m_message( message ),
      m_lineNumber( lineNumber )
{
}


/******************************************************************************/


RuntimeException* RuntimeException::undefinedOperator( const std::string& oprtr )
    throw()
{
    return new RuntimeException( UndefinedOperator, 0, oprtr );
}


/******************************************************************************/


RuntimeException* RuntimeException::undefinedMethod( const std::string& method )
    throw()
{
    return new RuntimeException( UndefinedMethod, 0, method );
}


} // end namespace cpps

