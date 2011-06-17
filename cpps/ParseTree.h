/**
 * @file
 *
 * @brief Describes the ParseTree class and its Node.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_PARSE_TREE_H_INCLUDED__
#define __CPPS_PARSE_TREE_H_INCLUDED__

#include <vector>

#include <Object.h>

namespace cpps
{

class ParseTree
{
public:
    typedef std::vector< ParseTree::Node > List;
    class Node
    {
    public:
        virtual Object::Reference getValue( Object::Reference ) = 0;

    }; // end class ParseTree::Node

private:
    Node::List statements;

public:
    ParseTree( void );

}; // end class ParseTree


namespace node
{

class TypeName : public Node
{
};
class Variable : public Node
{
};
class StringLiteral : public Node
{
};
class UnaryOperator : public Node
{
};
class BinaryOperator : public Node
{
};
class TernaryOperator : public Node
{
};
class 

} // end namespace node

} // emd namespace cpps

#endif // __CPPS_PARSE_TREE_H_INCLUDED__

