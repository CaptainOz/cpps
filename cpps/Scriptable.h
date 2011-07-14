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
    virtual const Scriptable& oprtrBitAnd( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrBitNot( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrBitOr( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrBitXOr( const Scriptable& rhs ) const;
    virtual Scriptable& oprtrCall( const Scriptable& args ); // Function call
    virtual const Scriptable& oprtrConcat( const Scriptable& args ) const;
    virtual const Scriptable& oprtrDivide( const Scriptable& args ) const;
    virtual const Scriptable& oprtrEquality( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrGreaterEqual( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrGreaterThan( const Scriptable& rhs ) const;
    virtual Scriptable& oprtrIndex( const Scriptable& index );
    virtual const Scriptable& oprtrInstanceOf( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrLeftShift( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrLessEqual( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrLessThan( const Scriptable& rhs ) const;
    virtual Scriptable& oprtrMemberAccess( const Scriptable& &rhs );
    virtual const Scriptable& oprtrMinus( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrModulo( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrMultiply( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrNegate( void ) const; // Unary minus
    virtual const Scriptable& oprtrNotEquality( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrPlus( const Scriptable& rhs ) const;
    virtual Scriptable& oprtrPostDecrement( void );
    virtual Scriptable& oprtrPostIncrement( void );
    virtual Scriptable& oprtrPreDecrement( void );
    virtual Scriptable& oprtrPreIncrement( void );
    virtual const Scriptable& oprtrRightShift( const Scriptable& rhs ) const;
    virtual const Scriptable& oprtrTypeName( void ) const;

private:
    unsigned int m_referenceCounter;

}; // end class Scriptable


inline std::ostream& operator<<( std::ostream& out, const Scriptable& obj )
{
    return out << obj.toString().c_str();
}

inline Scriptable& operator=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssign( rhs );
}

inline Scriptable& operator&=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignBitAnd( rhs );
}

inline Scriptable& operator~=( Scriptable& lhs, const Scriptable& rhs )
{
    return lhs.oprtrAssignBitNot( rhs );
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

inline const Scriptable& operator&( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrBitAnd( rhs );
}

inline const Scriptable& operator~( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrBitNot( rhs );
}

inline const Scriptable& operator|( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrBitOr( rhs );
}

inline const Scriptable& operator^( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrBitXOr( rhs );
}

inline Scriptable& operator()( Scriptable& lhs, const Scriptable& args )
{
    return lhs.oprtrCall( rhs );
}

inline const Scriptable& operator/( Scriptable& lhs, const Scriptable& args ) const
{
    return lhs.oprtrDivide( rhs );
}

inline const Scriptable& operator==( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrEquality( rhs );
}

inline const Scriptable& operator>=( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrGreaterEqual( rhs );
}

inline const Scriptable& operator>( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrGreaterThan( rhs );
}

inline Scriptable& operator[]( Scriptable& lhs, const Scriptable& index )
{
    return lhs.oprtrIndex( rhs );
}

inline const Scriptable& operator<<( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrLeftShift( rhs );
}

inline const Scriptable& operator<=( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrLessEqual( rhs );
}

inline const Scriptable& operator<( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrLessThan( rhs );
}

inline Scriptable& operator->( Scriptable& lhs, const Scriptable& &rhs )
{
    return lhs.oprtrMemberAccess( rhs );
}

inline const Scriptable& operator-( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrMinus( rhs );
}

inline const Scriptable& operator%( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrModulo( rhs );
}

inline const Scriptable& operator*( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrMultiply( rhs );
}

inline const Scriptable& operator-( Scriptable& lhs ) const
{
    return lhs.oprtrNegate();
}

inline const Scriptable& operator!=( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrNotEquality( rhs );
}

inline const Scriptable& operator+( Scriptable& lhs, const Scriptable& rhs ) const
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

inline const Scriptable& operator>>( Scriptable& lhs, const Scriptable& rhs ) const
{
    return lhs.oprtrRightShift( rhs );
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

