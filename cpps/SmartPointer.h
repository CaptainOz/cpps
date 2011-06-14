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
 *                     pre-increment, pre-decrement, and bool conversion
 *                     operators.
 */
template< typename DataType, typename CounterType = unsigned int >
class SmartPointer
{
private:
    typedef SmartPointer< DataType, CounterType > ThisType;
    CounterType* mRefCount;
    DataType* mDataPtr;

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

public:
    //! Empty constructor
    SmartPointer( void ) throw();

    //! Copy constructor
    /**
     * @param other The other SmartPointer to copy.
     */
    SmartPointer( const ThisType& other ) throw();

    //! Conversion constructor
    /**
     * @param dataPtr The pointer to convert into a SmartPointer.
     */
    SmartPointer( DataType* dataPtr ) throw();

    //! ~Destructor decrements the reference count and frees the pointer if it
    //! was the last one.
    ~SmartPointer( void ) throw();

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
    : mRefCount( NULL ),
      mDataPtr( NULL )
{
}

template< typename D, typename C >
SmartPointer<D,C>::SmartPointer( const ThisType& other ) throw()
    : mRefCount( NULL ),
      mDataPtr( NULL )
{
    _copy( other );
    _increment();
}

template< typename D, typename C >
SmartPointer<D,C>::SmartPointer( D* data ) throw()
    : mRefCount( new C(0) ),
      mDataPtr( data )
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
    if( mRefCount != NULL && --(*mRefCount) )
    {
        delete mRefCount;
        delete mDataPtr;
        mRefCount = NULL;
        mDataPtr = NULL;
    }
}


/******************************************************************************/


template< typename D, typename C >
inline void SmartPointer<D,C>::_increment( void ) throw()
{
    if( mRefCount != NULL )
        ++(*mRefCount);
}


/******************************************************************************/


template< typename D, typename C >
void SmartPointer<D,C>::_copy( const ThisType& other ) throw()
{
    ThisType* otherPtr = const_cast<ThisType*>( &other );
    mRefCount = otherPtr->mRefCount;
    mDataPtr  = otherPtr->mDataPtr;
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
    return *mDataPtr;
}

template< typename D, typename C >
inline D& SmartPointer<D,C>::operator*( void ) throw()
{
    return *mDataPtr;
}


/******************************************************************************/


template< typename D, typename C >
inline const D* SmartPointer<D,C>::operator->( void ) const throw()
{
    return mDataPtr;
}

template< typename D, typename C >
inline D* SmartPointer<D,C>::operator->( void ) throw()
{
    return mDataPtr;
}


} // end namespace cpps


#endif // __CPPS_SMART_POINTER_H_INCLUDED__

