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

template< typename DataType, typename RefCounterType = unsigned int >
class SmartPointerData_base
{
public:
    SmartPointerData_base( void ) {};
    virtual ~SmartPointerData_base( void ) {};

    virtual const DataType& getData( void ) const = 0;
    virtual DataType& getData( void ) = 0;
    
    virtual const RefCounterType& getCounter( void ) const = 0;
    virtual RefCounterType& getCounter( void ) = 0;
}; // end class SmartPointerData_base


template< typename DataType, typename RefCounterType = unsigned int >
class SmartPointerData : public SmartPointerData_base< DataType, RefCounterType >
{
private:
    typedef SmartPointerData< DataType, RefCounterType > ThisType;

    RefCounterType m_refCount;
    DataType* m_dataPtr;

public:
    SmartPointerData( void );
    SmartPointerData( const ThisType& other );
    SmartPointerData( const DataType& data );
    SmartPointerData( DataType* dataPtr );
    
    virtual ~SmartPointerData( void );
    
    virtual const DataType& getData( void ) const;
    virtual DataType& getData( void );

    virtual const RefCounterType& getCounter( void ) const;
    virtual RefCounterType& getCounter( void );
}; // end class SmartPointerData


//! A more advanced garbage collection class than auto_ptr.
/**
 * SmartPointers keep a count of the number of references to themselves and will
 * automatically free their memory once the number of references drops to zero.
 *
 * @tparam DataType       The type of data that the SmartPointer will point to.
 * @tparam RefCounterType The type to use to keep count of the number of
 *                        references to the SmartPointer. This type must support
 *                        the pre-increment, pre-decrement, bool conversion, and
 *                        unsigned int conversion operators.
 * @tparam ContainerType  The type to contain the data and reference counter
 *                        objects. This type should inherit from the template
 *                        class SmartPointerData_base.
 */
template<
        typename DataType,
        typename RefCounterType = unsigned int,
        typename ContainerType = SmartPointerData< DataType, RefCounterType >
    >
class SmartPointer
{
private:
    typedef SmartPointer< DataType, RefCounterType, ContainerType > ThisType;
    ContainerType* m_data;

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

    void _destroy( void ) throw();

public:
    //! Empty constructor
    SmartPointer( void ) throw();

    //! Copy constructor
    /**
     * Both SmartPointers will be pointing to the same instance of the data and
     * the reference counter will be incremented.
     *
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


template< typename D, typename R, typename C >
inline SmartPointer<D,R,C>::SmartPointer( void ) throw()
    : m_data( NULL )
{
}

template< typename D, typename R, typename C >
SmartPointer<D,R,C>::SmartPointer( const ThisType& other ) throw()
    : m_data( NULL )
{
    _copy( other );
    _increment();
}

template< typename D, typename R, typename C >
SmartPointer<D,R,C>::SmartPointer( D* dataPtr ) throw()
    : m_data( new C(dataPtr) )
{
}

template< typename D, typename R, typename C >
SmartPointer<D,R,C>::SmartPointer( const D& data ) throw()
    : m_data( new C(data) )
{
}


/******************************************************************************/


template< typename D, typename R, typename C >
inline SmartPointer<D,R,C>::~SmartPointer( void ) throw()
{
    _decrement();
}


/******************************************************************************/


template< typename D, typename R, typename C >
void SmartPointer<D,R,C>::_decrement( void ) throw()
{
    if( m_data != NULL && --(m_data->getCounter()) <= 0 )
        _destroy();
}


/******************************************************************************/


template< typename D, typename R, typename C >
inline void SmartPointer<D,R,C>::_increment( void ) throw()
{
    if( m_data != NULL )
        ++(m_data->getCounter());
}


/******************************************************************************/


template< typename D, typename R, typename C >
inline void SmartPointer<D,R,C>::_copy( const ThisType& other ) throw()
{
    m_data = (const_cast<ThisType*>( &other ))->m_data;
}


/******************************************************************************/


template< typename D, typename R, typename C >
void SmartPointer<D,R,C>::_destroy( void ) throw()
{
    delete m_data;
    m_data = NULL;
}


/******************************************************************************/


template< typename D, typename R, typename C >
inline unsigned int SmartPointer<D,R,C>::getReferenceCount( void ) const throw()
{
    return m_data == NULL ? 0 : m_data->getCounter();
}


/******************************************************************************/


template< typename D, typename R, typename C >
inline SmartPointer<D,R,C> SmartPointer<D,R,C>::clone( void ) const throw()
{
    return m_data == NULL ? ThisType() : ThisType( m_data->getData() );
}


/******************************************************************************/


template< typename D, typename R, typename C >
SmartPointer<D,R,C>& SmartPointer<D,R,C>::operator=( const ThisType& other ) throw()
{
    _decrement();
    _copy( other );
    _increment();
    return *this;
}


/******************************************************************************/


template< typename D, typename R, typename C >
inline const D& SmartPointer<D,R,C>::operator*( void ) const throw()
{
    return m_data->getData();
}

template< typename D, typename R, typename C >
inline D& SmartPointer<D,R,C>::operator*( void ) throw()
{
    return m_data->getData();
}


/******************************************************************************/


template< typename D, typename R, typename C >
inline const D* SmartPointer<D,R,C>::operator->( void ) const throw()
{
    return &(m_data->getData());
}

template< typename D, typename R, typename C >
inline D* SmartPointer<D,R,C>::operator->( void ) throw()
{
    return &(m_data->getData());
}


/******************************************************************************/


template< typename D, typename C >
SmartPointerData<D,C>::SmartPointerData( void )
    : m_refCount( 0 ),
      m_dataPtr( NULL )
{
}

template< typename D, typename C >
SmartPointerData<D,C>::SmartPointerData( const ThisType& other )
    : m_refCount( other.m_refCount ),
      m_dataPtr( new D( *(other.m_dataPtr) ) )
{
}

template< typename D, typename C >
SmartPointerData<D,C>::SmartPointerData( const D& data )
    : m_refCount( 1 ),
      m_dataPtr( new D( data ) )
{
}

template< typename D, typename C >
SmartPointerData<D,C>::SmartPointerData( D* dataPtr )
    : m_refCount( 1 ),
      m_dataPtr( dataPtr )
{
}


/******************************************************************************/


template< typename D, typename C >
SmartPointerData<D,C>::~SmartPointerData( void )
{
    if( m_dataPtr != NULL )
        delete m_dataPtr;
}


/******************************************************************************/


template< typename D, typename C >
inline const D& SmartPointerData<D,C>::getData( void ) const
{
    return *m_dataPtr;
}

template< typename D, typename C >
inline D& SmartPointerData<D,C>::getData( void )
{
    return *m_dataPtr;
}


/******************************************************************************/


template< typename D, typename C >
inline const C& SmartPointerData<D,C>::getCounter( void ) const
{
    return m_refCount;
}

template< typename D, typename C >
inline C& SmartPointerData<D,C>::getCounter( void )
{
    return m_refCount;
}


} // end namespace cpps


#endif // __CPPS_SMART_POINTER_H_INCLUDED__

