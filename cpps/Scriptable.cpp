/**
 *
 */

#include "Scriptable.h"

using namespace std;

namespace cpps
{


Scriptable::Reference Scriptable::oprtrAssign( const Scriptable::Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "Assign" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignBitAnd( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignBitAnd" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignBitNot( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignBitNot" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignBitOr( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignBitOr" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignBitXOr( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignBitXOr" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignConcat( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignConcat" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignDivide( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignDivide" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignLeftShift( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignLeftShift" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignMinus( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignMinus" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignModulo( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignModulo" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignMultiply( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignMultiply" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignPlus( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignPlus" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrAssignRightShift( const Reference& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignRightShift" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrBitAnd( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "BitAnd" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrBitNot( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "BitNot" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrBitOr( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "BitOr" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrBitXOr( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "BitXOr" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrCall( const Reference& args )
{
    throw RuntimeException::undefinedOperator( "Call" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrConcat( const Reference& args ) const
{
    throw RuntimeException::undefinedOperator( "Concat" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrDivide( const Reference& args ) const
{
    throw RuntimeException::undefinedOperator( "Divide" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrEquality( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Equality" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrGreaterEqual( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "GreaterEqual" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrGreaterThan( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "GreaterThan" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrIndex( const Reference& index )
{
    throw RuntimeException::undefinedOperator( "Index" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrInstanceOf( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "InstanceOf" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrLeftShift( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "LeftShift" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrLessEqual( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "LessEqual" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrLessThan( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "LessThan" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrMemberAccess( const Reference &rhs )
{
    throw RuntimeException::undefinedOperator( "MemberAccess" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrMinus( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Minus" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrModulo( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Modulo" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrMultiply( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Multiply" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrNegate( void ) const
{
    throw RuntimeException::undefinedOperator( "Negate" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrNotEquality( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "NotEquality" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrPlus( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Plus" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrPostDecrement( void )
{
    throw RuntimeException::undefinedOperator( "PostDecrement" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrPostIncrement( void )
{
    throw RuntimeException::undefinedOperator( "PostIncrement" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrPreDecrement( void )
{
    throw RuntimeException::undefinedOperator( "PreDecrement" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrPreIncrement( void )
{
    throw RuntimeException::undefinedOperator( "PreIncrement" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrRightShift( const Reference& rhs ) const
{
    throw RuntimeException::undefinedOperator( "RightShift" );
}


/******************************************************************************/


Scriptable::Reference Scriptable::oprtrTypeName( void ) const
{
    throw RuntimeException::undefinedOperator( "TypeName" );
}


/******************************************************************************/


string Scriptable::toString( void ) const
{
    throw RuntimeException::undefinedMethod( "toString" );
}


/******************************************************************************/


double Scriptable::toNumber( void ) const
{
    throw RuntimeException::undefinedMethod( "toNumber" );
}


/******************************************************************************/


bool Scriptable::toBool( void ) const
{
    throw RuntimeException::undefinedMethod( "toBool" );
}


} // end namespace cpps

