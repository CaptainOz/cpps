/**
 * @file
 *
 * @brief Describes a SmartPointer specialization for Scriptable.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_SCRIPTABLE_REFERENCE_H_INCLUDED__
#define __CPPS_SCRIPTABLE_REFERENCE_H_INCLUDED__

#include "SmartPointer.h"
#include "Scriptable.h"

namespace cpps
{

template<>
class SmartPointer< Scriptable, unsigned int >
{
private:
    void _destroy( void ) throw();
    void _copy( const Scriptable::Reference& other ) throw();

    unsigned int* const& _getCounter( void ) const throw();
    unsigned int*& _getCounter( void ) throw();

public:
    SmartPointer( Scriptable* dataPtr ) throw();

}; // end class SmartPointer< Scriptable >


/******************************************************************************/


template<>
void Scriptable::Reference::_destroy( void ) throw()
{
    // Since Scriptables contain their own reference counter we only need to
    // destroy the Scriptable object.
    delete m_dataPtr;
    m_refCount = NULL;
    m_dataPtr = NULL;
}


/******************************************************************************/


template<>
void Scriptable::Reference::_copy( const Scriptable::Reference& other )
    throw()
{
    Scriptable::Reference* otherPtr = const_cast<Scriptable::Reference*>( &other );
    _getDataPtr() = other->_getDataPtr();
}


/******************************************************************************/


template<>
unsigned int* const& Scriptable::Reference::_getCounter( void ) const throw()
{
    return _getDataPtr()->m_referenceCounter;
}

template<>
unsigned int*& Scriptable::Reference::_getCounter( void ) throw()
{
    return _getDataPtr()->m_referenceCounter;
}

} // end namespace cpps

#endif // __CPPS_SCRIPTABLE_REFERENCE_H_INCLUDED__

