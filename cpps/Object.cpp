/**
 *
 */

#include "Object.h"
#include "Number.h"

namespace cpps
{

Scriptable::Reference Object::oprtrDivide( const Scriptable& rhs ) const
{
    return Reference( new Number( toNumber() / rhs.toNumber() ) );
}


/******************************************************************************/


Scriptable::Reference Object::oprtrMinus( const Scriptable& rhs ) const
{
    return Reference( new Number( toNumber() - rhs.toNumber() ) );
}


/******************************************************************************/


Scriptable::Reference Object::oprtrModulo( const Scriptable& rhs ) const
{
    return Reference( new Number( (int)*this % (int)rhs ) );
}


/******************************************************************************/


Scriptable::Reference Object::oprtrMultiply( const Scriptable& rhs ) const
{
    return Reference( new Number( toNumber() * rhs.toNumber() ) );
}


/******************************************************************************/


Scriptable::Reference Object::oprtrNegate( void ) const
{
    return Reference( new Number( -toNumber() ) );
}


/******************************************************************************/


Scriptable::Reference Object::oprtrPlus( const Scriptable& rhs ) const
{
    return Reference( new Number( toNumber() + rhs.toNumber() ) );
}

} // end namespace cpps
