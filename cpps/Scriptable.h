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

#include "SmartPointer.h"

namespace cpps
{

//! Base class for all objects which can be put into the CPPS environment.
/**
 * This abstract class is used by anything that wants to be inserted into a CPPS
 * script.
 */
class Scriptable
{
public:
    typedef SmartPointer< Scriptable > Reference;

    //! Constructor and destructor do nothing.
    Scriptable( void );
    virtual ~Scriptable( void );

protected:
    virtual Reference oprtrAssign( const Reference& rhs );
    virtual Reference oprtrAssignBitAnd( const Reference& rhs );
    virtual Reference oprtrAssignBitNot( const Reference& rhs );
    virtual Reference oprtrAssignBitOr( const Reference& rhs );
    virtual Reference oprtrAssignBitXOr( const Reference& rhs );
    virtual Reference oprtrAssignConcat( const Reference& rhs );
    virtual Reference oprtrAssignDivide( const Reference& rhs );
    virtual Reference oprtrAssignLeftShift( const Reference& rhs );
    virtual Reference oprtrAssignMinus( const Reference& rhs );
    virtual Reference oprtrAssignModulo( const Reference& rhs );
    virtual Reference oprtrAssignMultiply( const Reference& rhs );
    virtual Reference oprtrAssignPlus( const Reference& rhs );
    virtual Reference oprtrAssignRightShift( const Reference& rhs );
    virtual Reference oprtrBitAnd( const Reference& rhs ) const;
    virtual Reference oprtrBitNot( const Reference& rhs ) const;
    virtual Reference oprtrBitOr( const Reference& rhs ) const;
    virtual Reference oprtrBitXOr( const Reference& rhs ) const;
    virtual Reference oprtrCall( const Reference& args ); // Function call
    virtual Reference oprtrConcat( const Reference& args ) const;
    virtual Reference oprtrDivide( const Reference& args ) const;
    virtual Reference oprtrEquality( const Reference& rhs ) const;
    virtual Reference oprtrGreaterEqual( const Reference& rhs ) const;
    virtual Reference oprtrGreaterThan( const Reference& rhs ) const;
    virtual Reference oprtrIndex( const Reference& index );
    virtual Reference oprtrInstanceOf( const Reference& rhs ) const;
    virtual Reference oprtrLeftShift( const Reference& rhs ) const;
    virtual Reference oprtrLessEqual( const Reference& rhs ) const;
    virtual Reference oprtrLessThan( const Reference& rhs ) const;
    virtual Reference oprtrMemberAccess( const Reference &rhs );
    virtual Reference oprtrMinus( const Reference& rhs ) const;
    virtual Reference oprtrModulo( const Reference& rhs ) const;
    virtual Reference oprtrMultiply( const Reference& rhs ) const;
    virtual Reference oprtrNegate( void ) const; // Unary minus
    virtual Reference oprtrNotEquality( const Reference& rhs ) const;
    virtual Reference oprtrPlus( const Reference& rhs ) const;
    virtual Reference oprtrPostDecrement( void );
    virtual Reference oprtrPostIncrement( void );
    virtual Reference oprtrPreDecrement( void );
    virtual Reference oprtrPreIncrement( void );
    virtual Reference oprtrRightShift( const Reference& rhs ) const;
    virtual Reference oprtrTypeName( void ) const;

}; // end class Scriptable


inline std::ostream operator<<( std::ostream& out, const Scriptable& obj )
{
    return out << obj.stringify();
}


/******************************************************************************/


inline Scriptable::Scriptable( void )
{
}


/******************************************************************************/


inline Scriptable::~Scriptable( void )
{
}


} // end namespace cpps

#endif // __CPPS_SCRIPTABLE_H_INCLUDED__

