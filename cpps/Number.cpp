/**
 *
 */

#include <cstdlib>
#include <cstdio>

#include "Number.h"

using namespace std;

namespace cpps
{


Number::Number( const string& val )
{
    // Convert the input string into a number.
    m_type = Integer;
    if( val.find( '.' ) != string::npos )
    {
        m_value = strtod( val.c_str(), NULL );
        m_type = Real;
    }
    else if( val.find( "0x" ) == 0 )
        m_value = strtol( val.substr(2).c_str(), NULL, 16 );
    else if( val.find( "0b" ) == 0 )
        m_value = strtol( val.substr(2).c_str(), NULL, 2 );
    else if( val.find( "0" ) == 0 )
        m_value = strtol( val.substr(1).c_str(), NULL, 8 );
    else if( val.find( "e" ) != string::npos )
        sscanf( val.c_str(), "%le", &m_value );
    else
        m_value = strtol( val.c_str(), NULL, 10 );

    // TODO: Add error handling.
}


/******************************************************************************/


double Number::toNumber( void ) const
{
    return m_value;
}


/******************************************************************************/


bool Number::toBool( void ) const
{
    return m_value != 0;
}



/******************************************************************************/


Scriptable::Reference Number::oprtrAssign( const Scriptable& rhs )
{
    m_value = rhs.toNumber();
    return Reference( this );
}


} // end namespace cpps

