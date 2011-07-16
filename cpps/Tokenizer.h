/**
 * @file
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_TOKENIZER_H_INCLUDED__
#define __CPPS_TOKENIZER_H_INCLUDED__

#include <sstream>
#include <string>

#include "Scriptable.h"
#include "Token.h"

namespace cpps
{

class Tokenizer
{
public:
    //! Code constructor
    /**
     * @param code The code string to tokenize.
     */
    Tokenizer( const std::string& code );

    //! Empty ~destructor.
    ~Tokenizer( void ) {}

    //! Gets the next token from the code stream.
    /**
     * @return The extracted token.
     */
    Token getNextToken( void );

private:
    std::stringstream m_codeStream;
    unsigned int m_lineCounter;
}; // end class Tokenizer


/*****************************************************************************/


inline Tokenizer::Tokenizer( const std::string& code )
    : m_codeStream( code ),
      m_lineCounter( 0 )
{
}


} // end namespace cpps

#endif // __CPPS_TOKENIZER_H_INCLUDED__
