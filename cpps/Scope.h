/**
 * @file Scope.h
 *
 * @brief Describes the Scope class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_SCOPE_H_INCLUDED__
#define __CPPS_SCOPE_H_INCLUDED__

#include <list>
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "Function.h"
#include "Nodes.h"
#include "Scriptable.h"
#include "Token.h"

namespace cpps
{

class Scope : public Scriptable
{
public:
    //! A syntax tree node for a single operation or value.
    class Node
    {
    private:
        enum Associativity
        {
            Left,
            Right
        };

        // TODO: Resolve cyclical reference between Node and nodeTypes
        nodeType::BinaryOperator* _getBinaryOperator(
                const Token::Type&   type,
                const Associativity& assoc
            );

        static void _getNode(
                      Node*& node,
                      Scope& scope,
                      Token::List::const_iterator& it,
                const Token::List::const_iterator& end
            );

        // TODO: Update these methods to return a more specific nodeType class.
        static Node* _getKeywordNode( const Token& keyword );
        static Node* _getVariableNode( const Token& varName );
        static Node* _getTypeNameNode( const Token& typeName );
        static Node* _getStringLiteralNode( const std::string& strValue );
        static Node* _getNumericLiteralNode( const std::string& numValue );
        static Node* _getUnaryOperatorNode( const Token::Type& type, const Node::Associativity& assoc );
        static Node* _getIndexOperatorNode( void );
        static Node* _getBinaryOperatorNode( const Token::Type& type );

    public:
        virtual Scriptable::Reference getValue( Scriptable::Reference args ) = 0;

    }; // end class Node

private:
    typedef std::vector< Node* > StatementList;
    StatementList mStatements;
    std::map< std::string, Object::Reference > mVariables;
    std::map< std::string, Function::Reference > mFunctions;

    typedef std::stack< Node* > ExecutionStack;
    typedef std::list< ExecutionStack > ExecutionStackList;
    ExecutionStackList mExecutionStacks;

    ExecutionStack* _parse( const Token::List& tokens );
    Node* _parse(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );

    Node* _parseLoop(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    Node* _parseBranch(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    Node* _parseTryCatch(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    Node* _parseBlock(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    Node* _parseStatement(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    Node* _parseExpression(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );

    void _addFunction(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    void _addNamespace(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    void _addClass(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );

public:
    Object exec(
            const std::string& code,
            unsigned in lineNumber = 0
        );

}; // end class Scope

} // end namespace cpps

#endif // __CPPS_SCOPE_H_INCLUDED__

