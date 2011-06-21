/**
 * @file Scope.h
 *
 * @brief Describes the Scope class.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_SCOPE_H_INCLUDED__
#define __CPPS_SCOPE_H_INCLUDED__

#include <map>
#include <string>
#include <vector>

#include "ParseTree.h"
#include "Scriptable.h"
#include "Token.h"

namespace cpps
{

class Scope : public Scriptable
{
private:
    std::vector< ParseTree::Node > mStatements;
    std::map< std::string, Object::Reference > mVariables;
    std::map< std::string, Function::Reference > mFunctions;

    ParseTree* _parse( const Token::List& tokens );
    ParseTree::Node* _parse(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );

    ParseTree::Node* _parseLoop(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    ParseTree::Node* _parseBranch(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    ParseTree::Node* _parseTryCatch(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    ParseTree::Node* _parseBlock(
                  Token::List::const_iterator& it,
            const Token::List::const_iterator& end
        );
    ParseTree::Node* _parseStatement(
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

