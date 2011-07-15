/**
 * @file Object.h
 *
 * @brief Header for the base object class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_OBJECT_H_INCLUDED__
#define __CPPS_OBJECT_H_INCLUDED__

#include <string>
#include "Scriptable.h"

namespace cpps
{

class Object : public Scriptable
{
private:
    int m_typeID;

public:
    Object( void );
    virtual ~Object( void );

    // TODO: Add operator actions.

}; // end class Object


/******************************************************************************/


inline Object::Object( void )
{
}


/******************************************************************************/


inline Object::~Object( void )
{
}


} // end namespace cpps

#endif // __CPPS_OBJECT_H_INCLUDED__

