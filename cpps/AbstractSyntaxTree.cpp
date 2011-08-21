/**
 * @file
 *
 * @author Nate Lillich
 */

#include "AbstractSyntaxTree.h"
#include "Nodes.h"

namespace cpps
{
typedef AbstractSyntaxTree AST;

AST::~AbstractSyntaxTree( void )
{
    if( m_root )
        delete m_root;
}


/*****************************************************************************/


void AST::addStatement( Node* statement )
{
    if( !m_root )
        m_root = new nodes::Block();
    ((nodes::Block*)m_root)->addStatement( statement );
}


} // end namespace cpps
