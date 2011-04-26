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

namespace cpps
{

class Object
{
private:
    TypeID mTypeID;

protected:
    Object( const TypeID& typeID );

public:
    std::string getType( void );

}; // end class Object

} // end namespace cpps

#endif __CPPS_OBJECT_H_INCLUDED__

