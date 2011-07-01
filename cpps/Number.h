/**
 *
 */

#ifndef __CPPS_NUMBER_H_INCLUDED__
#define __CPPS_NUMBER_H_INCLUDED__

#include <string>

#include "Scriptable.h"

namespace cpps
{

class Number : public Object
{
public:
    enum Type
    {
        Integer,
        Real
    }; // end enum Number::Type

    Number( void );
    Number( int val );
    Number( double val );
    explicit Number( const std::string& val );

    virtual ~Number( void ) {};

    virtual double toNumber( void ) const;
    virtual bool toBool( void ) const;

protected:
    // TODO: Add oprtr* methods here.

private:
    double m_value;
    Number::Type m_type;

}; // end class Number


/******************************************************************************/


inline Number::Number( void )
    : m_value( 0 ),
      m_type( Number::Real )
{
}

inline Number::Number( int val )
    : m_value( val ),
      m_type( Number::Integer )
{
}

inline Number::Number( double val )
    : m_value( val ),
      m_type( Number::Real )
{
}


} // end namespace cpps

#endif // __CPPS_NUMBER_H_INCLUDED__

