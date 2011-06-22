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
    ParseTree::Node* start = _parse( *tokens );

    // Execute
    return _executeStack( start );
}


/******************************************************************************/


ParseTree* Scope::_parse( const Token::List& tokens )
{
    const Token::List::const_iterator& begin = tokens.begin();
    const Token::List::const_iterator& end   = tokens.end();

    // Convert tokens into RPN stack.
    for( Token::List::const_iterator it = begin; it != end; ++it )
    {
        ParseTree::Node* statement = _parse( it, end );
        if( statement != NULL )
            mStatements.push( statement );
    }
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
    bool parsed = true;
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
        parsed = false;

    // If it isn't a block statement, lets extract a one-line statement.
    if( !parsed )
        statement = _parseStatement( it, end );
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


/******************************************************************************/


ParseTree::Node* Scope::_parseStatement(
              Token::List::const_iterator& it,
        const Token::List::const_iterator& end
    )
{
    // To simplify error checking here we'll assume that Scope::_parse correctly
    // checked for all the cases that would start a non-statement line.

    ParseTree::Node* start = NULL;
    for( ; it != end && (*it).getType() != Token::Semicolon; ++it )
    {
        const Token& token = *it;
        const Token::Type& type = token.getType();
        ParseTree::Node* node = NULL:
    
        // Is this token a keyword?
        if( type >= Token::Break && type <= Token::Var )
            node = ParseTree::Node::getKeywordNode( *it );

        // Or is this token a variable?
        else if( type == Token::Variable )
            node = ParseTree::Node::getVariableNode( *it );

        // Or is this a typename?
        else if( type == Token::TypeName )
            node = ParseTree::Node::getTypeNameNode( *it );

        // Or is this a string literal? For string literals we also concat
        // multiple ones together if they are directly next to each other.
        else if( type == Token::StringLiteral )
        {
            string value;
            for( ; it[1].getType() == Token::StringLiteral; ++it )
                value += (*it).getString();
            value += (*it).getString();
            node = ParseTree::Node::getStringLiteralNode( value );
        }

        // Or are we indexing?
        else if( type == Token::OpenBracket )
        {
            nodeType::IndexOperator* indexer = new nodeType::IndexOperator();
            ParseTree::Node* rightNode = _parseExpression( ++it, end, Token::CloseBracket );
            indexer.setRightOperand( rightNode );
            indexer.setLeftOperand( node );
            node = (ParseTree::Node*)indexer;
            ++it;
        }

        // TODO: Figure out how to handle parentheticals.
        // TODO: Consider doing the token checks in a ParseTree::Node::getNode
        //       method instead of here?
    }

    // If we reached the end of the file, that's an error! All statements must
    // end in semicolons.
    if( it == end )
        throw ParseExcetion(); // TODO: Fill out this exception.
    
    // Skip the semicolon at the end and return our starting node.
    ++it;
    return start;
}




} // end namespace cpps

