
#include "cpps/cpps.h"
#include "cpps/cpps.tab.hpp"
#include "cpps/cpps.lex.h"
#include "cpps/Parser.h"

namespace cpps {

Parser::Parser( std::istream* inStream ): m_inStream( inStream ){
    getStream() >> std::noskipws;
    cpps_lex_init( &scanner );
    cpps_set_extra( this, scanner );
}

// ---------------------------------------------------------------------------------------------- //

Parser::~Parser( void ){
    cpps_lex_destroy( scanner );
}

} // end namespace cpps