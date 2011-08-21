/**
 * @file
 *
 * Describes the Number class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_NUMBER_H_INCLUDED__
#define __CPPS_NUMBER_H_INCLUDED__

#include <string>

#include "Object.h"

namespace cpps
{

//! The numeric base type for CPPS.
/**
 * This is the base type used to represent number literals in CPPS.
 */
class Number : public Object
{
public:
    enum Type
    {
        Integer,
        Real
    }; // end enum Number::Type

    //! Default constructor
    Number( void );

    //! Integer constructor
    /**
     * @param val The value to initialize with.
     */
    Number( int val );

    //! Double constructor
    /**
     * @param val The value to initialize with.
     */
    Number( double val );

    //! String constructor
    /**
     * @param val The string to convert into a number.
     */
    explicit Number( const std::string& val );

    //! Virtual destructor does nothing.
    virtual ~Number( void ) {};

    //! Converts this cpps::Number to a double.
    /**
     * @return The floating point value of the Number.
     */
    virtual double toNumber( void ) const;

    //! Converts this
    /**
     * @return The boolean value of the Number (i.e. Number != 0).
     */
    virtual bool toBool( void ) const;

    //! Assigns another Scriptable's numeric value to this one.
    /**
     * @param rhs The right-hand-side Scriptable.
     *
     * @return A reference to this Number.
     */
    virtual Reference oprtrAssign( const Scriptable& rhs );

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

