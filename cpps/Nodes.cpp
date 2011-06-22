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

    // Or is this a string literal? For string literals we also concat
    // multiple ones together if they are directly next to each other.
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

    // TODO: NumericLiteral goes here.

    // Anything else means we didn't get a node.
    else
        nodeGot = false;

    // If one of the above statements got the node, return.
    if( nodeGot )
        return;

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
        // TODO: Move this logic to BinaryOperator::getAssociativity
        // Is this a right or left associative operator?
        Associativity assoc = Right;
        if( type == Token::LogicalOr  ||
            type == Token::LogicalAnd ||
           (type >= Token::Equality   && type <= Token::LessEqual) ||
           (type >= Token::RightShift && type <= Token::BitwiseOr) )
            assoc = Left;

        // Get the node for this operator and assign the left and right operands
        nodeType::BinaryOperator* oprtr = Node::_getBinaryOperator( type );
        Node* rightNode = scope._parseExpression( ++it, end, oprtr->getAssociativity() );
        oprtr.setRightOperand( rightNode );
        oprtr.setLeftOperand( node );
        node = (Node*)oprtr;
    }
}

} // end namespace cpps


