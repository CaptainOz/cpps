/**
 *
 */

#include "Nodes.h"
#include "Types.h"

namespace cpps
{

namespace nodes
{

UnaryOperator::UnaryOperator( AST::Node* operand )
{
    _addNode( operand );
}


/*****************************************************************************/


AST::Node* UnaryOperator::_operate( AST::Node** operands )
{
    return _operate( operands[0] );
}


/*****************************************************************************/


BinaryOperator::BinaryOperator( AST::Node* lhs, AST::Node* rhs )
{
    _addNode( lhs );
    _addNode( rhs );
}


/*****************************************************************************/


AST::Node* BinaryOperator::_operate( AST::Node** operands )
{
    return _operate( operands[0], operands[1] );
}


/*****************************************************************************/


TernaryOperator::TernaryOperator( AST::Node* lhs, AST::Node* mhs, AST::Node* rhs )
{
    _addNode( lhs );
    _addNode( mhs );
    _addNode( rhs );
}


/*****************************************************************************/


AST::Node* TernaryOperator::_operate( AST::Node** operands )
{
    return _operate( operands[0], operands[1], operands[2] );
}


/*****************************************************************************/


Scriptable::Reference Variable::getValue( void )
{
    return m_value;
}


/*****************************************************************************/


Scriptable::Reference NumericLiteral::getValue( void )
{
    return Scriptable::Reference( new Number( m_value ) );
}


/*****************************************************************************/


AST::Node* Addition::_operate( AST::Node* lhs, AST::Node* rhs )
{
    return new Variable( lhs->getValue()->oprtrPlus( *(rhs->getValue()) ) );
}


/*****************************************************************************/


AST::Node* Subtraction::_operate( AST::Node* lhs, AST::Node* rhs )
{
    return new Variable( lhs->getValue()->oprtrMinus( *(rhs->getValue()) ) );
}


/*****************************************************************************/


AST::Node* Multiplication::_operate( AST::Node* lhs, AST::Node* rhs )
{
    return new Variable( lhs->getValue()->oprtrMultiply( *(rhs->getValue()) ) );
}


/*****************************************************************************/


AST::Node* Division::_operate( AST::Node* lhs, AST::Node* rhs )
{
    return new Variable( lhs->getValue()->oprtrDivide( *(rhs->getValue()) ) );
}


/*****************************************************************************/


class Negation : public UnaryOperator
{
protected:
    AST::Node* _operate( AST::Node* operand ) override;

public:
    Negation( AST::Node* operand );
}; // end class Addition


/*****************************************************************************/


inline Negation::Negation( AST::Node* operand )
    : UnaryOperator( operand )
{
}





} // end namespace nodes

} // end namespace cpps


