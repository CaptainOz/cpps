/**
 * @file
 *
 * @brief Describes the Scriptable class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_SCRIPTABLE_H_INCLUDED__
#define __CPPS_SCRIPTABLE_H_INCLUDED__

#include <iostream>
#include <string>

#include "SmartPointer.h"

namespace cpps
{

//! Base class for all objects which can be put into the CPPS environment.
/**
 * This abstract class is used by anything that wants to be inserted into a CPPS
 * script.
 */
class Scriptable : public SmartPointerData_base< Scriptable >
{
public:
    typedef SmartPointer< Scriptable, unsigned int, Scriptable > Reference;

    //! Constructor and destructor do nothing.
    Scriptable( void );
    virtual ~Scriptable( void );

    //! Converts this object to a printable string.
    virtual std::string toString( void ) const;

    //! Converts this object to a number.
    virtual double toNumber( void ) const;

    //! Converts this object to true or false.
    virtual bool toBool( void ) const;

    const Scriptable& getData( void ) const;
    Scriptable& getData( void );
    
    const unsigned int& getCounter( void ) const;
    unsigned int& getCounter( void );

    virtual Scriptable& oprtrAssign( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignBitAnd( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignBitNot( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignBitOr( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignBitXOr( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignConcat( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignDivide( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignLeftShift( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignMinus( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignModulo( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignMultiply( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignPlus( const Scriptable& rhs );
    virtual Scriptable& oprtrAssignRightShift( const Scriptable& rhs );
    virtual Scriptable  oprtrBitAnd( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrBitNot( void ) const;
    virtual Scriptable  oprtrBitOr( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrBitXOr( const Scriptable& rhs ) const;
    virtual Scriptable& oprtrCall( Scriptable& args ); // Function call
    virtual Scriptable  oprtrConcat( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrDivide( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrEquality( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrGreaterEqual( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrGreaterThan( const Scriptable& rhs ) const;
    virtual Scriptable& oprtrIndex( const Scriptable& index );
    virtual Scriptable  oprtrInstanceOf( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrLeftShift( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrLessEqual( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrLessThan( const Scriptable& rhs ) const;
    virtual Scriptable& oprtrMemberAccess( const Scriptable& rhs );
    virtual Scriptable  oprtrMinus( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrModulo( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrMultiply( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrNegate( void ) const; // Unary minus
    virtual Scriptable  oprtrNotEquality( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrPlus( const Scriptable& rhs ) const;
    virtual Scriptable& oprtrPostDecrement( void );
    virtual Scriptable& oprtrPostIncrement( void );
    virtual Scriptable& oprtrPreDecrement( void );
    virtual Scriptable& oprtrPreIncrement( void );
    virtual Scriptable  oprtrRightShift( const Scriptable& rhs ) const;
    virtual Scriptable  oprtrTypeName( void ) const;

    Scriptable& operator=( const Scriptable& rhs );
    Scriptable& operator()( Scriptable& args );
    Scriptable& operator[]( const Scriptable& index );

    explicit operator std::string( void ) const;
    explicit operator short( void ) const;
    explicit operator int( void ) const;
    explicit operator long( void ) const;
    explicit operator long long( void ) const;
    explicit operator float( void ) const;
    explicit operator double( void ) const;
    explicit operator bool( void ) const;

private:
    unsigned int m_referenceCounter;

}; // end class Scriptable


inline std::ostream& operator<<( std::ostream& out, const Scriptable& obj )
{
    return out << obj.toString().c_str();
}

inline Scriptable& Scriptable::operator=( const Scriptable& rhs )
{
    return oprtrAssign( rhs );
}

inline Scriptable& operator&=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignBitAnd( rhs );
}

inline Scriptable& operator|=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignBitOr( rhs );
}

inline Scriptable& operator^=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignBitXOr( rhs );
}

inline Scriptable& operator/=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignDivide( rhs );
}

inline Scriptable& operator<<=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignLeftShift( rhs );
}

inline Scriptable& operator-=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignMinus( rhs );
}

inline Scriptable& operator%=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignModulo( rhs );
}

inline Scriptable& operator*=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignMultiply( rhs );
}

inline Scriptable& operator+=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignPlus( rhs );
}

inline Scriptable& operator>>=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignRightShift( rhs );
}

inline Scriptable operator&( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrBitAnd( rhs );
}

inline Scriptable operator~( const Scriptable& lhs )
{
    return lhs.oprtrBitNot();
}

inline Scriptable operator|( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrBitOr( rhs );
}

inline Scriptable operator^( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrBitXOr( rhs );
}

inline Scriptable& Scriptable::operator()( Scriptable& args )
{
    return oprtrCall( args );
}

inline Scriptable operator/( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrDivide( rhs );
}

inline Scriptable operator==( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrEquality( rhs );
}

inline Scriptable operator>=( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrGreaterEqual( rhs );
}

inline Scriptable operator>( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrGreaterThan( rhs );
}

inline Scriptable& Scriptable::operator[]( const Scriptable& index )
{
    return oprtrIndex( index );
}

inline Scriptable operator<<( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrLeftShift( rhs );
}

inline Scriptable operator<=( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrLessEqual( rhs );
}

inline Scriptable operator<( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrLessThan( rhs );
}

inline Scriptable operator-( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrMinus( rhs );
}

inline Scriptable operator%( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrModulo( rhs );
}

inline Scriptable operator*( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrMultiply( rhs );
}

inline Scriptable operator-( const Scriptable& lhs )
{
    return lhs.oprtrNegate();
}

inline Scriptable operator!=( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrNotEquality( rhs );
}

inline Scriptable operator+( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrPlus( rhs );
}

inline Scriptable& operator--( Scriptable& lhs, int x )
{
    return lhs.oprtrPostDecrement();
}

inline Scriptable& operator++( Scriptable& lhs, int x )
{
    return lhs.oprtrPostIncrement();
}

inline Scriptable& operator--( Scriptable& lhs )
{
    return lhs.oprtrPreDecrement();
}

inline Scriptable& operator++( Scriptable& lhs )
{
    return lhs.oprtrPreIncrement();
}

inline Scriptable operator>>( const Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrRightShift( rhs );
}


/******************************************************************************/


inline Scriptable::operator std::string( void ) const
{
    return toString();
}


/******************************************************************************/


inline Scriptable::operator short( void ) const
{
    return (short)toNumber();
}


/******************************************************************************/


inline Scriptable::operator int( void ) const
{
    return (int)toNumber();
}


/******************************************************************************/


inline Scriptable::operator long( void ) const
{
    return (long)toNumber();
}


/******************************************************************************/


inline Scriptable::operator long long( void ) const
{
    return (long long)toNumber();
}


/******************************************************************************/


inline Scriptable::operator float( void ) const
{
    return (float)toNumber();
}


/******************************************************************************/


inline Scriptable::operator double( void ) const
{
    return (double)toNumber();
}


/******************************************************************************/


inline Scriptable::operator bool( void ) const
{
    return toBool();
}


/******************************************************************************/


inline Scriptable::Scriptable( void )
    : m_referenceCounter( 0 )
{
}


/******************************************************************************/


inline Scriptable::~Scriptable( void )
{
}


/******************************************************************************/


inline const Scriptable& Scriptable::getData( void ) const
{
    return *this;
}

inline Scriptable& Scriptable::getData( void )
{
    return *this;
}


/******************************************************************************/


inline const unsigned int& Scriptable::getCounter( void ) const
{
    return m_referenceCounter;
}

inline unsigned int& Scriptable::getCounter( void )
{
    return m_referenceCounter;
}


} // end namespace cpps

#endif // __CPPS_SCRIPTABLE_H_INCLUDED__

