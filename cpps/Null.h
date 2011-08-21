///
///
///

#ifndef __CPPS_NULL_H_INCLUDED__
#define __CPPS_NULL_H_INCLUDED__

#include <string>

#include "Scriptable.h"

namespace cpps
{

class Null : public Scriptable
{
public:
    // TODO: Define all the operators for NULL.

    std::string toString( void ) const;
    double toNumber( void ) const;
    bool toBool( void ) const;

    static Scriptable::Reference NullReference( Null() );
}; // end class Null


/*****************************************************************************/


inline std::string Null::toString( void ) const
{
    return "";
}


/*****************************************************************************/


inline double Null::toNumber( void ) const
{
    return 0;
}


/*****************************************************************************/


inline bool Null::toBool( void ) const
{
    return false;
}

} // end namespace cpps

#endif // __CPPS_NULL_H_INCLUDED__
