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

} // end namespace cpps

