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
    virtual const char* what( void ) throw();

private:
    const ParseException::Type mType;
    const std::string mMessage;
    const unsigned int mLineNumber;
    std::string mCodeLine;
    int mOffset;

}; // end class ParseException


/******************************************************************************/


class RuntimeException : public std::exception
{
public:
    enum Type
    {
        UndefinedOperator,
        UndefinedMethod,
        Scripted
    }; // end RuntimeException::Type

    RuntimeException(
            const RuntimeException::Type& exceptionType,
            const unsigned int& lineNumber,
            const std::string&  message
        ) throw();

    virtual ~RuntimeException( void ) throw() {}
    virtual const char* what( void ) throw();

    static RuntimeException* undefinedOperator( const std::string& oprtr )
            throw();
    static RuntimeException* undefinedMethod( const std::string& method )
            throw();

private:
    const RuntimeException::Type& m_type;
    const std::string  m_message;
    const unsigned int m_lineNumber;
}; // end class RuntimeException

} // end namespace cpps

#endif // __CPPS_EXCEPTIONS_H_INCLUDED__

