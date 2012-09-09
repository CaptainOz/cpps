
#pragma once

#include <istream>
#include <string>

namespace cpps {

class Parser {
private:
    std::istream*   m_inStream;
    void*           m_scanner;

public:
    Parser( void );
    Parser( std::istream& inStream );

    ~Parser( void );

    int lookupKeyword( const std::string& str ) const;

    void parse( void );
    void parse( std::istream& inStream );

    std::istream& getStream( void );
    void* getScanner( void );
}; // end class Parser

// ---------------------------------------------------------------------------------------------- //

inline std::istream& Parser::getStream( void ){
    return *m_inStream;
}

// ---------------------------------------------------------------------------------------------- //

inline void* Parser::getScanner( void ){
    return m_scanner;
}

} // end namespace cpps
