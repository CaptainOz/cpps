/**
 * @file
 *
 * @brief Describes the Function class which is the base type for all function
 *        instances in CPPS.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_FUNCTION_H_INCLUDED__
#define __CPPS_FUNCTION_H_INCLUDED__

#include "Scope.h"
#include "SmartPointer.h"

namespace cpps
{
/* Temporarilly disabled
class Function : public Scope
{
public:
    typedef SmartPointer< Function > Reference;

    Scriptable::Reference call( Sciptable::Reference args );
}; // end class Function
*/
} // end namespace cpps

#endif // __CPPS_FUNCTION_H_INCLUDED__

