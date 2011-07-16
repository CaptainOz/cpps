/**
 *
 */

#include "Object.h"
#include "Number.h"

namespace cpps
{

Scriptable Object::oprtrDivide( const Scriptable& rhs ) const
{
    return Number( toNumber() / rhs.toNumber() );
}


/******************************************************************************/


Scriptable Object::oprtrMinus( const Scriptable& rhs ) const
{
    return Number( toNumber() - rhs.toNumber() );
}


/******************************************************************************/


Scriptable Object::oprtrModulo( const Scriptable& rhs ) const
{
    return Number( (int)*this % (int)rhs );
}


/******************************************************************************/


Scriptable Object::oprtrMultiply( const Scriptable& rhs ) const
{
    return Number( toNumber() * rhs.toNumber() );
}


/******************************************************************************/


Scriptable Object::oprtrNegate( void ) const
{
    return Number( -toNumber() );
}


/******************************************************************************/


Scriptable Object::oprtrPlus( const Scriptable& rhs ) const
{
    return Number( toNumber() + rhs.toNumber() );
}

} // end namespace cpps
