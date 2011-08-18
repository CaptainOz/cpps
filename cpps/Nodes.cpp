/**
 *
 */

#include "Nodes.h"

namespace cpps
{

namespace ast
{

AST::Node* UnaryOperator::_operate( AST::Node** operands )
{
    return _operate( operands[0] );
}

AST::Node* BinaryOperator::_operate( AST::Node** operands )
{
    return _operate( operands[0], operands[1] );
}

AST::Node* TernaryOperator::_operate( AST::Node** operands )
{
    return _operate( operands[0], operands[1], operands[2] );
}

} // end namespace ast

} // end namespace cpps


