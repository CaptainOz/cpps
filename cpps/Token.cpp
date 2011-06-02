/**
 *
 */

#include <cctype>

using namespace std;

namespace cpps
{

const char* Token::TypeNames[] = {
        "TypeName",        // [a-zA-Z_]\w*
        "Identifier",      // \$[a-zA-Z_]\w*
        "StringLiteral",   // (['"]).*?(?<!\\)\1
        "NumericLiteral",  // (?:\d+|\d*\.\d+)
        "Scope",           // ::
        "MemberAccess",    // ->
        "Semicolon",       // ;
        "Colon",           // :
        "Comma",           // ,
        "Plus",            // \+
        "Minus",           // -
        "Multiply",        // \*
        "Divide",          // /
        "Modulo",          // %
        "Concat",          // \.
        "Increment",       // \+\+
        "Decrement",       // --
        "OpenParen",       // \(
        "CloseParen",      // \)
        "OpenBrace",       // \{
        "CloseBrace",      // \}
        "OpenBracket",     // \[
        "CloseBracket",    // \]
        "LogicalNot",      // !
        "LogicalOr",       // \|\|
        "LogicalAnd",      // &&
        "Equality",        // ==
        "NotEquality",     // !=
        "GreaterThan",     // >
        "LessThan",        // <
        "GreaterEqual",    // >=
        "LessEqual",       // <=
        "Assign",          // =
        "AssignPlus",      // \+=
        "AssignMinus",     // -=
        "AssignMultiply",  // \*=
        "AssignDivide",    // /=
        "AssignModulo",    // %=
        "AssignBitAnd",    // &=
        "AssignBitXOr",    // \^=
        "AssignBitOr",     // |=
        "AssignLeftShift", // <<=
        "AssignRightShift",// >>=
        "BitwiseNot",      // ~
        "BitwiseAnd",      // &
        "BitwiseXOr",      // \^
        "BitwiseOr",       // \|
        "TypeNameOperator",// typename
        "SizeOf",          // sizeof
        "InstanceOf",      // instanceof
        "New",             // new
        "Delete",          // delete
        "RighShift",       // >>
        "LeftShift",       // <<
        "TernaryIf",       // \?
        "CommentLine",     // \/\/[^\n]*
        "CommentBlock",    // \/\*.*?\*\/
        "RegexMatch",      // \/.?(?<!\\)\/

        0 // End array
    };

Token::List Token::tokenize( const string& code )
{
    unsigned int lineCounter = 0;
    int codeLength = code.size();
    Token::List tokenList;

    for( int pos = 0; pos < codeLength; ++pos )
    {
        const char& thisC = code[pos];
        const char& nextC = code[pos+1];

        // Skip whitespace.
        if( isspace( thisC ) )
        {
            if( thisC == '\n' )
                ++lineCounter;
            continue;
        }

        // Are we starting a string literal? (StringLiteral)
        if( thisC == '\'' || thisC == '"' )
            tokenList.push_back( Token::_extractString( code, pos ) );

        // Or possibly a variable identifier? (Identifier)
        else if( thisC == '$' )
            tokenList.push_back( Token::_extractIdentifier( code, pos ) );

        // Or a scope operator? (Scope)
        else if( thisC == ':' && nextC == ':' )
            tokenList.push_back( Token::_extractScope( code, pos ) );

        // Or a pre/post increment? (Incrememnt)
        else if( thisC == '+' && nextC == '+' )
            tokenList.push_back( Token::_extractIncrement( code, pos ) );

        // Or a pre/post decrement? (Decrement)
        else if( thisC == '-' && nextC == '-' )
            tokenList.push_back( Token::_extractDecrement( code, pos ) );

        // Or possibly a parenthesized expression? (OpenParen/CloseParen)
        else if( thisC == '(' || thisC == ')' )
            tokenList.push_back( Token::_extractChar( code, pos, thisC ) );

        // Or possibly an array indexing? (OpenBracket/CloseBracket)
        else if( thisC == '[' || thisC == ']' )
            tokenList.push_back( Token::_extractChar( code, pos, thisC ) );

        // Or a member accessor operator? (MemberAccess)
        else if( thisC == '-' && nextC == '>' )
            tokenList.push_back( Token::_extactMemberAccess( code, pos ) );

        // Or are we getting a typename? (TypeNameOperator)
        else if( Token::_canBeKeyword( code, pos, "typename" ) )
            tokenList.push_back( Token::_extractTypeNameOperator( code, pos ) );

        // Or possibly getting the sizeof a variable? (SizeOf)
        else if( Token::_canBeKeyword( code, pos, "sizeof" ) )
            tokenList.push_back( Token::_extractSizeOf( code, pos ) );

        // Or checking the class type of a variable? (InstanceOf)
        else if( Token::_canBeKeyword( code, pos, "instanceof" ) )
            tokenList.push_back( Token::_extractInstanceOf( code, pos ) );

        // Or creating a new object? (New)
        else if( Token::_canBeKeyword( code, pos, "new" ) )
            tokenList.push_back( Token::_extractNew( code, pos ) );

        // Or deleting an object? (Delete)
        else if( Token::_canBeKeyword( code, pos, "delete" ) )
            tokenList.push_back( Token::_extractDelete( code, pos ) );

        // Or is this a plus-assignment? (AssignPlus)
        else if( thisC == '+' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignPlus( code, pos ) );

        // Or is this a minus-assignment? (AssignMinus)
        else if( thisC == '-' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignMinus( code, pos ) );

        // Or is this a multiply-assignment? (AssignMultiply)
        else if( thisC == '*' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignMultiply( code, pos ) );

        // Or is this a divide-assignment? (AssignDivide)
        else if( thisC == '/' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignDivide( code, pos ) );

        // Or is this a modulo-assignment? (AssignModulo)
        else if( thisC == '%' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignModulo( code, pos ) );

        // Or is this a bitwise-and-assignment? (AssignBitAnd)
        else if( thisC == '&' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignBitAnd( code, pos ) );

        // Or is this a bitwise-xor-assignment? (AssignBitXOr)
        else if( thisC == '^' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignBitXOr( code, pos ) );

        // Or is this a bitwise-or-assignment? (AssignBitOr)
        else if( thisC == '|' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignBitOr( code, pos ) );

        // Or is this a left-shift-assignment? (AssignLeftShift)
        else if( thisC == '<' && nextC == '<' && code[pos+2] == '=' )
            tokenList.push_back( Token::_extractAssignLeftShift( code, pos ) );

        // Or is this a right-shift-assignment? (AssignRightShift)
        else if( thisC == '>' && nextC == '>' && code[pos+2] == '=' )
            tokenList.push_back( Token::_extractAssignRightShift( code, pos ) );

        // Or possibly a string concatenation operator? (Concat)
        else if( thisC == '.' && !isdigit( nextC ) )
            tokenList.push_back( Token::_extractChar( code, pos, thisC ) );

        // Or is this a numeric literal? (NumericLiteral)
        else if( isdigit( thisC ) || thisC == '.' )
            tokenList.push_back( Token::_extractNumber( code, pos ) );

        // 
    }
}


/******************************************************************************/


bool Token::_canBeKeyword(
        const string& code,
        const int&    pos,
        const string& keyword
    )
{
    const int   keywordSize = keyword.size();
    const char& charAfter   = code[ pos + keywordSize ];
    return code[pos] == keyword[0]                    && // starts with same char
           code.substr( pos, keywordSize ) == keyword && // following substring matches
          !isalnum( charAfter )                       && // char after is not alphanumeric
           charAfter != '_';                             // char after is not underscore
}


} // end namespace cpps
