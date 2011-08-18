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


//! This namespace contains all the Scope::Node subclasses.
namespace ast
{

typedef AbstractSyntaxTree AST;

template< unsigned int operandCount >
class Operator : public AST::Node
{
    unsigned int m_setOperands;
	AST::Node* m_operands[ operandCount ];

protected:
	virtual AST::Node* _operate( AST::Node** operands ) = 0;
    AST::Node** _getOperands( void );
    void _addNode( AST::Node* node );

public:
    Operator( void );
    Scriptable::Reference getValue( void ) override;
}; // end class Operator

template< unsigned int c >
Operator<c>::Operator( void )
    : m_setOperands( 0 ),
      m_operands( NULL )
{
}

template< unsigned int c >
void Operator<c>::_addNode( AST::Node* node )
{
    if( m_setOperands == c )
        throw "InvalidStateException";
    m_operands[ m_setOperands++ ] = node;
}

template< unsigned int c >
Scriptable::Reference Operator<c>::getValue( void )
{
    return _operate( _getOperands() )->getValue();
}

template< unsigned int c >
inline AST::Node** Operator<c>::_getOperands( void )
{
    return m_operands;
}


/*****************************************************************************/


class UnaryOperator : public Operator<1>
{
    AST::Node* _operate( AST::Node** operands ) override;
    virtual AST::Node* _operate( AST::Node* operand ) = 0;
}; // end class UnaryOperator


/*****************************************************************************/


class BinaryOperator : public Operator<2>
{
protected:
    AST::Node* _operate( AST::Node** operands ) override;
    virtual AST::Node* _operate( AST::Node* lhs, AST::Node* rhs ) = 0;
}; // end class BinaryOperator


/*****************************************************************************/


class TernaryOperator : public Operator<3>
{
protected:
    AST::Node* _operate( AST::Node** operands ) override;
    virtual AST::Node* _operate( AST::Node* lhs, AST::Node* mhs, AST::Node* rhs ) = 0;
}; // end class TernaryOperator


/*****************************************************************************/


/**
 * Contains a reference to a variable in the tree.
 */
class Variable : public AST::Node
{
    Scriptable::Reference m_value;

public:
    Scriptable::Reference getValue( void );
}; // end class Variable


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


} // end namespace ast


} // emd namespace cpps

#endif // __CPPS_NODES_H_INCLUDED__

