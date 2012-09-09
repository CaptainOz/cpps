
#pragma once

#include <string>

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

inline std::istream& Parser::getStream( void ){
    return *m_inStream;
}

} // end namespace cpps
