/**
 * @file
 *
 * @brief Describes the SmartPointer class.
 *
 * @author Nate Lillich
 */


#ifndef __CPPS_SMART_POINTER_H_INCLUDED__
#define __CPPS_SMART_POINTER_H_INCLUDED__


namespace cpps
{


//! A more advanced garbage collection class than auto_ptr.
/**
 * SmartPointers keep a count of the number of references to themselves and will
 * automatically free their memory once the number of references drops to zero.
 *
 * @tparam DataType    The type of data that the SmartPointer will point to.
 * @tparam CounterType The type to use to keep count of the number of references
 *                     to the SmartPointer. This type must support the
 *                     pre-increment, pre-decrement, bool conversion, and
 *                     unsigned int conversion operators.
 */
template< typename DataType, typename CounterType = unsigned int >
class SmartPointer
{
private:
    typedef SmartPointer< DataType, CounterType > ThisType;
    CounterType* m_refCount;
    DataType* m_dataPtr;

    //! Copy constructor used by SmartPointer::cast.
    SmartPointer( DataType* dataPtr, CounterType* counter ) throw();

    //! Decrements our reference counter and frees the data if we have dropped
    //! to zero references.
    void _decrement( void ) throw();

    //! Increments our reference counter only if we have data we are referencing
    void _increment( void ) throw();

    //! Copies the other SmartPointer into this one.
    /**
     * After this, both SmartPointers will point to the same data and have the
     * same reference count.
     *
     * @param other The other SmartPointer to copy.
     */
    void _copy( const ThisType& other ) throw();

    //! Returns a reference to the reference counter pointer.
    CounterType* const& _getCounter( void ) const throw();
    CounterType*& _getCounter( void ) throw();

    //! Returns a reference to the data pointer.
    DataType* const& _getDataPtr( void ) const throw();
    DataType*& _getDataPtr( void ) throw();

    void _destroy( void ) throw();

public:
    //! Empty constructor
    SmartPointer( void ) throw();

    //! Copy constructor
    /**
     * @param other The other SmartPointer to copy.
     */
    SmartPointer( const ThisType& other ) throw();

    //! Pointer conversion constructor
    /**
     * @param dataPtr The pointer to convert into a SmartPointer.
     */
    SmartPointer( DataType* dataPtr ) throw();

    //! Data conversion constructor
    /**
     * @param data The data to create a SmartPointer copy of.
     */
    explicit SmartPointer( const DataType& data ) throw();

    //! ~Destructor decrements the reference count and frees the pointer if it
    //! was the last one.
    ~SmartPointer( void ) throw();

    //! Gets the count of the number of references to this SmartPointer.
    /**
     * @return The total number of references to this SmartPointer. This value
     *         can be zero if this SmartPointer points to nothing.
     */
    unsigned int getReferenceCount( void ) const throw();

    //! Creates a new copy of the referenced object with a separate reference
    //! counter.
    /**
     * @return A new copy of the referenced object with a separete counter.
     */
    ThisType clone( void ) const throw();

    //! Casts this smart pointer to a pointer of another type.
    template< typename CastType >
    SmartPointer< CastType, CounterType > castTo( void ) throw();

    //! Copy operator
    /**
     * @param other The other SmartPointer to copy.
     *
     * @return A reference to this SmartPointer.
     */
    ThisType& operator=( const ThisType& other ) throw();

    //! Data accessor.
    /**
     * @return A reference to the data controlled by this SmartPointer.
     */
    const DataType& operator*( void ) const throw();
    DataType& operator*( void ) throw();

    //! Data member/method accessor.
    /**
     * @return A pointer to the data controlled by this SmartPointer.
     */
    const DataType* operator->( void ) const throw();
    DataType* operator->( void ) throw();
}; // end class SmartPointer


/******************************************************************************/


template< typename D, typename C >
inline SmartPointer<D,C>::SmartPointer( void ) throw()
    : m_refCount( NULL ),
      m_dataPtr( NULL )
{
}

template< typename D, typename C >
SmartPointer<D,C>::SmartPointer( const ThisType& other ) throw()
    : m_refCount( NULL ),
      m_dataPtr( NULL )
{
    _copy( other );
    _increment();
}

template< typename D, typename C >
SmartPointer<D,C>::SmartPointer( D* dataPtr ) throw()
    : m_refCount( new C(0) ),
      m_dataPtr( dataPtr )
{
    _increment();
}

template< typename D, typename C >
SmartPointer<D,C>::SmartPointer( const D& data ) throw()
    : m_refCount( new C(0) ),
      m_dataPtr( new D(data) )
{
    _increment();
}

template< typename D, typename C >
SmartPointer<D,C>::SmartPointer( D* dataPtr, C* counter ) throw()
    : m_refCount( counter ),
      m_dataPtr( dataPtr )
{
    _increment();
}


/******************************************************************************/


template< typename D, typename C >
inline SmartPointer<D,C>::~SmartPointer( void ) throw()
{
    _decrement();
}


/******************************************************************************/


template< typename D, typename C >
void SmartPointer<D,C>::_decrement( void ) throw()
{
    C*& refCount = _getCounter();
    if( refCount != NULL && --(*refCount) <= 0 )
        _destroy();
}


/******************************************************************************/


template< typename D, typename C >
inline void SmartPointer<D,C>::_increment( void ) throw()
{
    C*& refCount = _getCounter();
    if( refCount != NULL )
        ++(*refCount);
}


/******************************************************************************/


template< typename D, typename C >
void SmartPointer<D,C>::_copy( const ThisType& other ) throw()
{
    ThisType* otherPtr = const_cast<ThisType*>( &other );
    _getCounter() = otherPtr->_getCounter();
    _getDataPtr() = otherPtr->_getDataPtr();
}


/******************************************************************************/


template< typename D, typename C >
inline C* const& SmartPointer<D,C>::_getCounter( void ) const throw()
{
    return m_refCount;
}

template< typename D, typename C >
inline C*& SmartPointer<D,C>::_getCounter( void ) throw()
{
    return m_refCount;
}


/******************************************************************************/


template< typename D, typename C >
inline D* const& SmartPointer<D,C>::_getDataPtr( void ) const throw()
{
    return m_dataPtr;
}

template< typename D, typename C >
inline D*& SmartPointer<D,C>::_getDataPtr( void ) throw()
{
    return m_dataPtr;
}


/******************************************************************************/


template< typename D, typename C >
void SmartPointer<D,C>::_destroy( void ) throw()
{
    delete m_refCount;
    delete m_dataPtr;
    m_refCount = NULL;
    m_dataPtr = NULL;
}


/******************************************************************************/


template< typename D, typename C >
inline unsigned int SmartPointer<D,C>::getReferenceCount( void ) const throw()
{
    C* const& refCount = _getCounter();
    return refCount != NULL ? *refCount : 0;
}


/******************************************************************************/


template< typename D, typename C >
inline SmartPointer<D,C> SmartPointer<D,C>::clone( void ) const throw()
{
    return ThisType( *_getDataPtr() );
}


/******************************************************************************/


template< typename D, typename C >
template< typename CastType >
inline SmartPointer< CastType, C > SmartPointer<D,C>::castTo( void ) throw()
{
    CastType* newDataPtr = dynamic_cast<CastType*>(_getDataPtr());
    return SmartPointer< CastType, C >( newDataPtr, _getCounter() );
}


/******************************************************************************/


template< typename D, typename C >
SmartPointer<D,C>& SmartPointer<D,C>::operator=( const ThisType& other ) throw()
{
    _decrement();
    _copy( other );
    _increment();
    return *this;
}


/******************************************************************************/


template< typename D, typename C >
inline const D& SmartPointer<D,C>::operator*( void ) const throw()
{
    return *_getDataPtr();
}

template< typename D, typename C >
inline D& SmartPointer<D,C>::operator*( void ) throw()
{
    return *_getDataPtr();
}


/******************************************************************************/


template< typename D, typename C >
inline const D* SmartPointer<D,C>::operator->( void ) const throw()
{
    return _getDataPtr();
}

template< typename D, typename C >
inline D* SmartPointer<D,C>::operator->( void ) throw()
{
    return _getDataPtr();
}


} // end namespace cpps


#endif // __CPPS_SMART_POINTER_H_INCLUDED__

