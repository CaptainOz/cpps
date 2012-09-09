
#include "cpps/cpps.h"
#include "cpps/cpps.tab.hpp"
#include "cpps/cpps.lex.h"
#include "cpps/Parser.h"

namespace cpps {

Parser::Parser( void ): m_inStream( nullptr ){
    cpps_lex_init( &m_scanner );
    cpps_set_extra( this, m_scanner );
}

// ---------------------------------------------------------------------------------------------- //

Parser::Parser( std::istream& inStream ): m_inStream( &inStream ){
    if( m_inStream ){
        getStream() >> std::noskipws;
    }
    cpps_lex_init( &m_scanner );
    cpps_set_extra( this, m_scanner );
}

// ---------------------------------------------------------------------------------------------- //

Parser::~Parser( void ){
    cpps_lex_destroy( m_scanner );
}

// ---------------------------------------------------------------------------------------------- //

int Parser::lookupKeyword( const std::string& str ) const {
    if( str == "while" ){
        return WHILE;
    }
    else if( str == "if" ){
        return IF;
    }
    else if( str == "else" ){
        return ELSE;
    }
    else if( str == "print" ){
        return PRINT;
    }
    else {
        return 0;
    }
}

// ---------------------------------------------------------------------------------------------- //

void Parser::parse( void ){
    cpps_parse( this );
}

// ---------------------------------------------------------------------------------------------- //

void Parser::parse( std::istream& inStream ){
    m_inStream = &inStream;
    inStream >> std::noskipws;
    parse();
}

} // end namespace cpps
