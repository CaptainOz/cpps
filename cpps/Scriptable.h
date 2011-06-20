/**
 * @file
 *
 * @brief Describes the Scriptable class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_SCRIPTABLE_H_INCLUDED__
#define __CPPS_SCRIPTABLE_H_INCLUDED__

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
    ~Scriptable( void );

}; // end class Scriptable


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

