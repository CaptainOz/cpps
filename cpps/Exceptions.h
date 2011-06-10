/**
 *
 */

#ifndef __CPPS_EXCEPTIONS_H_INCLUDED__
#define __CPPS_EXCEPTIONS_H_INCLUDED__

#include <exception>
#include <string>

namespace cpps
{

class ParseException : public std::exception
{
public:
    enum Type
    {
        InvalidName,
        UnexpectedToken,
        UnknownToken
    }; // end ParseException::Type

    ParseException(
            const ParseException::Type& exceptionType,
            const std::string&  code,
            const          int& offset,
            const unsigned int& lineNumber,
            const std::string&  message
        ) throw();

    virtual ~ParseException( void ) throw() {}

private:
    const ParseException::Type mType;
    const std::string mMessage;
    const unsigned int mLineNumber;
    std::string mCodeLine;
    int mOffset;

}; // end class ParseException

} // end namespace cpps

#endif // __CPPS_EXCEPTIONS_H_INCLUDED__

