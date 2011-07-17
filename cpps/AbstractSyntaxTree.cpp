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


} // end namespace cpps
