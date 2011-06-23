/**
 *
 */

#include "Nodes.h"

namespace cpps
{

void Scope::Node::_getNode(
              Node*& node,
              Scope& scope,
              Token::List::const_iterator& it,
        const Token::List::const_iterator& end
    )
{
    const Token& token = *it;
    const Token::Type& type = token.getType();

    // TODO: Figure out how to handle typecasting and parentheticals
    // TODO: Add ternary operator support.

    // Is this token a keyword?
    bool nodeGot = true;
    if( type >= Token::Break && type <= Token::Var )
        node = Node::_getKeywordNode( *it );

    // Or is this token a variable?
    else if( type == Token::Variable )
        node = Node::_getVariableNode( *it );

    // Or is this a typename?
    else if( type == Token::TypeName )
        node = Node::_getTypeNameNode( *it );

    // Or is this a string literal? For string literals we also concat multiple
    // strings together if they are directly next to each other.
    else if( type == Token::StringLiteral )
    {
        string value;
        do
        {
            value += (*it).getString();
        } while( ++it != end && (*it).getType() == Token::StringLiteral );
        node = Node::_getStringLiteralNode( value );

        // Back the iterator up one spot so we end on the last StringLiteral.
        --it;
    }

    // Or is this a numeric literal?
    else if( type == Token::NumericLiteral )
        node = Node::_getNumericLiteralNode( token->getString(), negative );

    // Anything else means we didn't get a node.
    else
        nodeGot = false;

    // If one of the above statements got the node, return.
    if( nodeGot )
        return;

    // Right-associative unary operators require that no nodes be in the
    // expression yet.
    if( node == NULL              &&
       (type == Token::Increment  ||
        type == Token::Decrement  ||
        type == Token::New        ||
        type == Token::SizeOf     ||
        type == Token::Delete     ||
        type == Token::BitwiseAnd || // Reference operator
        type == Token::LogicalNot ||
        type == Token::BitwiseNot ||
        type == Token::Plus       || // Sign negation
        type == Token::Minus)      )
    {
        // Get the operator node.
        nodeType::UnaryOperator* oprtr = Node::_getUnaryOperatorNode( type, Right );

        // Get and set the operand.
        Node* operand = scope._parseExpression( ++it, end, Right );
        oprtr->setOperand( operand );
        node = oprtr;
        return;
    }

    // Everything below this point requires a token to have come before it.
    if( node == NULL )
        throw ParseException(); // TODO: Fill out this parse exception.

    // TODO: Add post(in|de)crement operators here-ish.

    // Are we indexing?
    if( type == Token::OpenBracket )
    {
        nodeType::BinaryOperator* indexer = Node::_getIndexOperatorNode();
        Node* rightNode = scope._parseExpression( ++it, end, Token::CloseBracket );
        indexer.setRightOperand( rightNode );
        indexer.setLeftOperand( node );
        node = (Node*)indexer;
        ++it;
    }

    // Possibly a binary operator?
    //     Operators               Tokens  Associativity
    // Member accessing         ->              L
    // Multiplication           *               L
    // Division                 /               L
    // Modulo                   %               L
    // Addition                 +               L
    // Subtraction              -               L
    // Concatenation            .               L
    // Bit shifting             <<  >>          L
    // Relational operators     <   <=  >  =>   L
    // Equality                 ==  !=          L
    // Bitwise operators        &   ^   |       L
    // Logical operators        &&  ||          L
    // Assignment               =               R
    // Assign sum/difference    +=  -=          R
    // Assign product           *=              R
    // Assign quotient          /=              R
    // Assign remainder         %=              R
    // Assign shift             <<= >>=         R
    // Assign bitwise operation &=  ^=  |=      R
    else if( type == Token::LogicalOr  ||
             type == Token::LogicalAnd ||
            (type >= Token::Equality   && type <= Token::AssignRightShift) ||
            (type >= Token::RightShift && type <= Token::BitwiseOr) )
    {
        // Is this a right or left associative operator?
        Node::Associativity assoc = Right;
        if( type == Token::LogicalOr  ||
            type == Token::LogicalAnd ||
           (type >= Token::Equality   && type <= Token::LessEqual) ||
           (type >= Token::RightShift && type <= Token::BitwiseOr) )
            assoc = Left;

        // Get the node for this operator and assign the left and right operands
        nodeType::BinaryOperator* oprtr = Node::_getBinaryOperatorNode( type );
        Node* rightNode = scope._parseExpression( ++it, end, assoc );
        oprtr.setRightOperand( rightNode );
        oprtr.setLeftOperand( node );
        node = (Node*)oprtr;
    }
}

} // end namespace cpps


