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
    int mTypeID;

protected:
    Object( const int& typeID );

public:
    std::string getType( void );
    std::string toString( void );

}; // end class Object

} // end namespace cpps

#endif // __CPPS_OBJECT_H_INCLUDED__

