
#pragma once

#include <string>

#include "cpps/cpps.tab.hpp"

namespace cpps {

class Parser {
private:
    std::istream* m_inStream;

public:
    void* scanner;
    int result;

    Parser( std::istream* inStream = &std::cin );

    ~Parser( void );

    int lookupKeyword( const std::string& str ) const;

    std::istream& getStream( void );
}; // end class Parser

// ---------------------------------------------------------------------------------------------- //

inline int Parser::lookupKeyword( const std::string& str ) const {
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

inline std::istream& Parser::getStream( void ){
    return *m_inStream;
}

} // end namespace cpps
