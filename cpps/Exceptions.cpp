/**
 *
 */

#include <sstream>

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
    unsigned int end;
    for( end = offset; end < code.size() && code[ end ] != '\n'; ++end )
    {}  // Do nothing in loop.

    // Take the substring between them and get the offset from the substr.
    mCodeLine = code.substr( start, end );
    mOffset = offset - start;
}


/******************************************************************************/


const char* ParseException::what( void ) const throw()
{
    ostringstream ss;
    const string& type = mType == InvalidName     ? "InvalidName"     :
                         mType == UnexpectedToken ? "UnexpectedToken" :
                         mType == UnknownToken    ? "UnknownToken"    :
                                                    "UnknownError"    ;
    ss << "ParseException (" << type << "): " << mMessage << " at line "
       << mLineNumber << " char " << mOffset << ": " << mCodeLine;
    return ss.str().c_str();
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


/******************************************************************************/


const char* RuntimeException::what( void ) const throw()
{
    ostringstream ss;
    const string& type = m_type == UndefinedOperator ? "UndefinedOperator" :
                         m_type == UndefinedMethod   ? "UndefinedMethod"   :
                         m_type == Scripted          ? "std::Exception"    :
                                                       "UnknownError"      ;
    ss << "RuntimeException (" << type << "): " << m_message << " at line "
       << m_lineNumber;
    return ss.str().c_str();
}


} // end namespace cpps

