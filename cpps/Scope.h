/**
 * @file Scope.h
 *
 * @brief Describes the Scope class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_SCOPE_H_INCLUDED__
#define __CPPS_SCOPE_H_INCLUDED__

#include "Scriptable.h"

namespace cpps
{

class Scope : public Scriptable
{
private:

public:
    Object exec(
            const std::string& code,
            unsigned in lineNumber = 0
        );

}; // end class Scope

} // end namespace cpps

#endif // __CPPS_SCOPE_H_INCLUDED__

