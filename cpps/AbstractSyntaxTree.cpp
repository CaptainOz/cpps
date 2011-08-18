/**
 * @file
 *
 * @author Nate Lillich
 */

#include "AbstractSyntaxTree.h"

namespace cpps
{

typedef AbstractSyntaxTree AST;

AST::~AbstractSyntaxTree( void )
{
    if( m_root )
        delete m_root;
}


/*****************************************************************************/


AST::Node* AST::addStatement( Node* statement )
{
}


/*****************************************************************************/


AST::Node* AST::addVariable( Node* variable )
{
}


/*****************************************************************************/


AST::Node* AST::addStringLiteral( Node* stringLiteral )
{
}


/*****************************************************************************/


AST::Node* AST::addNumericLiteral( Node* numericLiteral )
{
}


/*****************************************************************************/


AST::Node* AST::addAddition( Node* lhs, Node* rhs )
{
}


/*****************************************************************************/


AST::Node* AST::addMinus( Node* lhs, Node* rhs )
{
}


/*****************************************************************************/


AST::Node* AST::addMultiply( Node* lhs, Node* rhs )
{
}


/*****************************************************************************/


AST::Node* AST::addDivide( Node* lhs, Node* rhs )
{
}


/*****************************************************************************/


AST::Node* AST::addNegate( Node* node )
{
}


} // end namespace cpps
