/**
 * @file
 *
 * @brief Contains the code for the Scope class.
 *
 * @author Nate Lillich
 */


#include "Scope.h"

using namespace std;

namespace cpps
{

Scope::Scope( void )
{
}


/******************************************************************************/


Object Scope::exec(
        const    string& code,
        unsigned int     lineNumber
    )
{
    // Tokenize
    Token::List* tokens = Token::tokenize( code );

    // Parse
    ParseTree* statements = _parse( *tokens );

    // Execute
    // Convert RPN into op-code where needed
    // Replace constant expressions with their values
}


/******************************************************************************/


ParseTree* Scope::_parse( const Token::List& tokens )
{
    ParseTree *ptree = new ParseTree();
    const Token::List::const_iterator& begin = tokens.begin();
    const Token::List::const_iterator& end   = tokens.end();

    // Convert tokens into RPN stack.
    for( Token::List::const_iterator it = begin; it != end; ++it )
    {
        ParseTree::Node* statement = _parse( it, end );
        if( statement != NULL );
        ptree.addStatement( statement );
    }

    // Create function and block structures as encountered
}


ParseTree::Node* Scope::_parse(
              Token::List::const_iterator& it,
        const Token::List::const_iterator& end
    )
{
    // Set up the variables we'll be referencing in this loop.
    const Token&           token     = *it;
    const Token*           nextToken = (it+1 == end) ? &(it[1]) : 0;
    const Token::Type&     thisType  = token.getType();
    const Token::Type&     nextType  = nextToken ? nextToken->getType() : Token::TokenTypeCount;
          ParseTree::Node* statement = NULL;

    // Functions, namespaces, classes, structs, and unions all get added to
    // the scope directly not parsed into statements.
    bool block = true;
    if( thisType == Token::Function ||
       (thisType == Token::TypeName && nextType == Token::Function) )
        _addFunction( it, end );
    else if( thisType == Token::Namespace )
        _addNamespace( it, end );
    else if( thisType == Token::Class  ||
             thisType == Token::Struct ||
             thisType == Token::Union   )
        _addClass( it, end );

    // Parse out all the other block statements next. There are few of them
    // and they are easy to detect.
    else if( thisType == Token::For     ||
             thisType == Token::Foreach ||
             thisType == Token::Do      ||
             thisType == Token::While    )
        statement = _parseLoop( it, end );
    else if( thisType == Token::If )
        statement = _parseBranch( it, end );
    else if( thisType == Token::Try )
        statement = _parseTryCatch( it, end );
    else if( thisType == Token::OpenBrace )
        statement = _parseBlock( it, end );
    else
        block = false;

    // If it isn't a block statement, lets extract a one-line statement.
    if( !block )
        statement = _parseStatement( it, end );

    // If we still haven't parsed this statement, then its an error.
    if( !block && !statement )
        throw ParseException(
                ParseException::UnexpectedToken,
                token.getString(),
                0,
                token.getLineNumber(),
                "Unexpected token of type " + token.getTypeString()
            );
    return statement;
}

void Scope::_addFunction(
              Token::List::const_iterator& it,
        const Token::List::const_iterator& end
    )
{
    // Figure out the function's return type.
    string returnType = "";
    if( (*it).getType() == Token::TypeName )
    {
        returnType = (*it).getString();
        ++it;
    }

    // Skip the function token and get the function's name.
    ++it;
    if( it == end )
        throw ParseException::unexpectedEndOfFile();
    if( (*it).getType() != Token::TypeName )
        throw ParseException::unexpectedToken(
                (*it), 0, Token::getTypeString( Token::TypeName ) );
    string name = (*it).getString();
    ++it;

    // Now we are at the parameter list, so loop through until we find the
    // closing parenthesis.
    if( (*it).getType() != Token::OpenParen )
        throw ParseException::unexpectedToken(
                (*it), 0, Token::getTypeString( Token::OpenParen ) );
    vector< Object > parameterList;
    for( ++it; (*it).getType() != Token::CloseParen; ++it )
    {
        // We should never reach the end while parsing the parameter list!
        if( it+1 == end )
            throw ParseException::unexpectedEndOfFile();
        
    }
}

void _addNamespace(
              Token::List::const_iterator& it,
        const Token::List::const_iterator& end
    );
void _addClass(
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




} // end namespace cpps
