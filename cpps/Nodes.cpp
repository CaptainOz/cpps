/**
 *
 */

#include "Nodes.h"

namespace cpps
{

void Scope::Node::getNode(
              Node*& node,
              Scope& scope,
              Token::List::const_iterator& it,
        const Token::List::const_iterator& end
    )
{
    const Token& token = *it;
    const Token::Type& type = token.getType();

    // Is this token a keyword?
    bool nodeGot = true;
    if( type >= Token::Break && type <= Token::Var )
        node = Node::getKeywordNode( *it );

    // Or is this token a variable?
    else if( type == Token::Variable )
        node = Node::getVariableNode( *it );

    // Or is this a typename?
    else if( type == Token::TypeName )
        node = Node::getTypeNameNode( *it );

    // Or is this a string literal? For string literals we also concat multiple
    // strings together if they are directly next to each other.
    else if( type == Token::StringLiteral )
    {
        string value;
        do
        {
            value += (*it).getString();
        } while( ++it != end && (*it).getType() == Token::StringLiteral );
        node = Node::getStringLiteralNode( value );

        // Back the iterator up one spot so we end on the last StringLiteral.
        --it;
    }

    // TODO: This conditional is super fugly. Make it more readable.
    // Or is this a numeric literal?
    else if( type == Token::NumericLiteral ||
            ((type == Token::Plus || type == Token::Minus) &&
             it+1 != end && it[1].getType() == Token::NumericLiteral) )
    {
        // Calculate any sign negation and skip to the number.
        const bool negative = (type == Token::Minus);
        if( type != Token::NumericLieral )
            ++it;

        // Get the node
        node = Node::getNumericLiteral( (*it)->getString(), negative );
    }

    // TODO: TypeCast goes here?
    
    // TODO: LogicalNot goes here.
    
    // TODO: BitwiseNot goes here.

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
        type == Token::BitwiseNot) )
    {
        // Get the operator node.
        nodeType::UnaryOperator* oprtr = Node::getUnaryOperator( type, Right );

        // Get and set the operand.
        Node* operand = scope._parseExpression( ++it, end, Right );
        oprtr->setOperand( operand );
    }

    // Everything below this point requires a token to have come before it.
    if( node == NULL )
        throw ParseException(); // TODO: Fill out this parse exception.

    // Are we indexing?
    if( type == Token::OpenBracket )
    {
        nodeType::IndexOperator* indexer = new nodeType::IndexOperator();
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
        Associativity assoc = Right;
        if( type == Token::LogicalOr  ||
            type == Token::LogicalAnd ||
           (type >= Token::Equality   && type <= Token::LessEqual) ||
           (type >= Token::RightShift && type <= Token::BitwiseOr) )
            assoc = Left;

        // Get the node for this operator and assign the left and right operands
        nodeType::BinaryOperator* oprtr = Node::_getBinaryOperator( type );
        Node* rightNode = scope._parseExpression( ++it, end, assoc );
        oprtr.setRightOperand( rightNode );
        oprtr.setLeftOperand( node );
        node = (Node*)oprtr;
    }
}

} // end namespace cpps


