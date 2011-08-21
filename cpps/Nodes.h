/**
 * @file
 *
 * @brief Describes Scope::Node subclasses.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_NODES_H_INCLUDED__
#define __CPPS_NODES_H_INCLUDED__

#include <vector>

#include "AbstractSyntaxTree.h"

namespace cpps
{


/// This namespace contains all the AbstractSyntaxTree::Node subclasses.
namespace nodes
{
typedef AbstractSyntaxTree AST;

/// Base class for all Operator nodes.
///
/// @tparam operandCount The number of operands the operator takes. The maximum
//                       number of operands is 255.
template< unsigned char operandCount >
class Operator : public AST::Node
{
    unsigned char m_setOperands;
	AST::Node* m_operands[ operandCount ];

protected:
	virtual AST::Node* _operate( AST::Node** operands ) = 0;
    AST::Node** _getOperands( void );
    void _addNode( AST::Node* node );

public:
    Operator( void );
    Scriptable::Reference getValue( void );
}; // end class Operator

template< unsigned char c >
Operator<c>::Operator( void )
    : m_setOperands( 0 ),
      m_operands( NULL )
{
}

template< unsigned char c >
void Operator<c>::_addNode( AST::Node* node )
{
    if( m_setOperands == c )
        throw "InvalidStateException";
    m_operands[ m_setOperands++ ] = node;
}

template< unsigned char c >
Scriptable::Reference Operator<c>::getValue( void )
{
    return _operate( _getOperands() )->getValue();
}

template< unsigned char c >
inline AST::Node** Operator<c>::_getOperands( void )
{
    return m_operands;
}


/*****************************************************************************/


class UnaryOperator : public Operator<1>
{
protected:
    AST::Node* _operate( AST::Node** operands );
    virtual AST::Node* _operate( AST::Node* operand ) = 0;

public:
    UnaryOperator( AST::Node* operand );
}; // end class UnaryOperator


/*****************************************************************************/


class BinaryOperator : public Operator<2>
{
protected:
    AST::Node* _operate( AST::Node** operands );
    virtual AST::Node* _operate( AST::Node* lhs, AST::Node* rhs ) = 0;

public:
    BinaryOperator( AST::Node* lhs, AST::Node* rhs );
}; // end class BinaryOperator


/*****************************************************************************/


class TernaryOperator : public Operator<3>
{
protected:
    AST::Node* _operate( AST::Node** operands );
    virtual AST::Node* _operate( AST::Node* lhs, AST::Node* mhs, AST::Node* rhs ) = 0;

public:
    TernaryOperator( AST::Node* lhs, AST::Node* mhs, AST::Node* rhs );
}; // end class TernaryOperator


/*****************************************************************************/


/**
 * Contains a reference to a variable in the tree.
 */
class Variable : public AST::Node
{
    Scriptable::Reference m_value;

public:
    Variable( const Scriptable::Reference& value );
    Scriptable::Reference getValue( void );
}; // end class Variable


/*****************************************************************************/


inline Variable::Variable( const Scriptable::Reference& value )
    : m_value( value )
{
}


/*****************************************************************************/


class Block : public AST::Node
{
    typedef std::vector<AST::Node*> StatementList;
    StatementList m_statements;
}; // end class Block


/*****************************************************************************/


class Function : public AST::Node
{
    AST::Node* m_body;
};


/*****************************************************************************/


class Addition : public BinaryOperator
{
protected:
    AST::Node* _operate( AST::Node* lhs, AST::Node* rhs );

public:
    Addition( AST::Node* lhs, AST::Node* rhs );
}; // end class Addition


/*****************************************************************************/


inline Addition::Addition( AST::Node* lhs, AST::Node* rhs )
    : BinaryOperator( lhs, rhs )
{
}


/*****************************************************************************/


class Subtraction : public BinaryOperator
{
protected:
    AST::Node* _operate( AST::Node* lhs, AST::Node* rhs );

public:
    Subtraction( AST::Node* lhs, AST::Node* rhs );
}; // end class Addition


/*****************************************************************************/


inline Subtraction::Subtraction( AST::Node* lhs, AST::Node* rhs )
    : BinaryOperator( lhs, rhs )
{
}


/*****************************************************************************/


class Multiplication : public BinaryOperator
{
protected:
    AST::Node* _operate( AST::Node* lhs, AST::Node* rhs );

public:
    Multiplication( AST::Node* lhs, AST::Node* rhs );
}; // end class Addition


/*****************************************************************************/


inline Multiplication::Multiplication( AST::Node* lhs, AST::Node* rhs )
    : BinaryOperator( lhs, rhs )
{
}


/*****************************************************************************/


class Division : public BinaryOperator
{
protected:
    AST::Node* _operate( AST::Node* lhs, AST::Node* rhs );

public:
    Division( AST::Node* lhs, AST::Node* rhs );
}; // end class Addition


/*****************************************************************************/


inline Division::Division( AST::Node* lhs, AST::Node* rhs )
    : BinaryOperator( lhs, rhs )
{
}


/*****************************************************************************/


class Negation : public UnaryOperator
{
protected:
    AST::Node* _operate( AST::Node* operand );

public:
    Negation( AST::Node* operand );
}; // end class Addition


/*****************************************************************************/


inline Negation::Negation( AST::Node* operand )
    : UnaryOperator( operand )
{
}


} // end namespace nodes


} // emd namespace cpps

#endif // __CPPS_NODES_H_INCLUDED__

