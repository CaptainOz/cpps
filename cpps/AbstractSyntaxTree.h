/**
 * @file
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_ABSTRACT_SYNTAX_TREE_H_INCLUDED__
#define __CPPS_ABSTRACT_SYNTAX_TREE_H_INCLUDED__

#include "Scriptable.h"

namespace cpps
{

class AbstractSyntaxTree
{
public:
    class Node
    {
    protected:
        //! Right-sizes the node's datastructures.
        virtual void _finalize( void );

        virtual void _addNode( Node* node );

    public:
        Node( void );
        virtual ~Node( void );

        virtual Scriptable::Reference getValue( void );
    }; // end class AbstractSyntaxTree::Node

private:
    Node* m_root;
    Node* m_working;

public:
    AbstractSyntaxTree( void );
    ~AbstractSyntaxTree( void );

    /// Resets the AST by removing the root node.
    ///
    /// @note The root node is not deleted, simply forgotten. Use
    ///       AbstractSyntaxTree::clear to delete the nodes in the tree.
    void reset( void );
}; // end class AbstractSyntaxTree


/*****************************************************************************/


inline AbstractSyntaxTree::AbstractSyntaxTree( void )
    : m_root( NULL ),
      m_working( NULL )
{
}


/*****************************************************************************/


inline AbstractSyntaxTree::Node::Node( void )
{
}


} // end namespace cpps

#endif // __CPPS_ABSTRACT_SYNTAX_TREE_H_INCLUDED__
