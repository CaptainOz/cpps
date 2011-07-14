/**
 *
 */

#include "Exceptions.h"
#include "Scriptable.h"

using namespace std;

namespace cpps
{


Scriptable& Scriptable::oprtrAssign( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "Assign" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignBitAnd( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignBitAnd" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignBitNot( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignBitNot" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignBitOr( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignBitOr" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignBitXOr( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignBitXOr" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignConcat( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignConcat" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignDivide( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignDivide" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignLeftShift( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignLeftShift" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignMinus( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignMinus" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignModulo( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignModulo" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignMultiply( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignMultiply" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignPlus( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignPlus" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrAssignRightShift( const Scriptable& rhs )
{
    throw RuntimeException::undefinedOperator( "AssignRightShift" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrBitAnd( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "BitAnd" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrBitNot( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "BitNot" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrBitOr( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "BitOr" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrBitXOr( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "BitXOr" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrCall( const Scriptable& args )
{
    throw RuntimeException::undefinedOperator( "Call" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrConcat( const Scriptable& args ) const
{
    throw RuntimeException::undefinedOperator( "Concat" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrDivide( const Scriptable& args ) const
{
    throw RuntimeException::undefinedOperator( "Divide" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrEquality( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Equality" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrGreaterEqual( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "GreaterEqual" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrGreaterThan( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "GreaterThan" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrIndex( const Scriptable& index )
{
    throw RuntimeException::undefinedOperator( "Index" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrInstanceOf( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "InstanceOf" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrLeftShift( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "LeftShift" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrLessEqual( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "LessEqual" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrLessThan( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "LessThan" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrMemberAccess( const Reference &rhs )
{
    throw RuntimeException::undefinedOperator( "MemberAccess" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrMinus( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Minus" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrModulo( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Modulo" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrMultiply( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Multiply" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrNegate( void ) const
{
    throw RuntimeException::undefinedOperator( "Negate" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrNotEquality( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "NotEquality" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrPlus( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "Plus" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrPostDecrement( void )
{
    throw RuntimeException::undefinedOperator( "PostDecrement" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrPostIncrement( void )
{
    throw RuntimeException::undefinedOperator( "PostIncrement" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrPreDecrement( void )
{
    throw RuntimeException::undefinedOperator( "PreDecrement" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrPreIncrement( void )
{
    throw RuntimeException::undefinedOperator( "PreIncrement" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrRightShift( const Scriptable& rhs ) const
{
    throw RuntimeException::undefinedOperator( "RightShift" );
}


/******************************************************************************/


Scriptable& Scriptable::oprtrTypeName( void ) const
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

