/**
 * @file
 *
 * @brief Describes the Scriptable class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_SCRIPTABLE_H_INCLUDED__
#define __CPPS_SCRIPTABLE_H_INCLUDED__

#include <map>
#include <string>

#include "SmartPointer.h"

namespace cpps
{

//! Base class for all objects which can be put into the CPPS environment.
/**
 * This abstract class is used by anything that wants to be inserted into a CPPS
 * script.
 *
 * @par Abstract Methods:
 * @li accessor Access an individual property of the Scriptable object.
 */
class Scriptable
{
public:
    typedef SmartPointer< Scriptable > Reference;
    typedef std::map< std::string, Reference > Attributes;

private:
    Attributes mAttrs;

protected:
    virtual Reference accessor( const std::string& name ) = 0;

public:
    Reference operator[]( const std::string& name );
}; // end class Scriptable


/******************************************************************************/


inline Scriptable::Reference Scriptable::operator[]( const std::string& name )
{
    return accessor( name );
}


} // end namespace cpps

#endif // __CPPS_SCRIPTABLE_H_INCLUDED__

