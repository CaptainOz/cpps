/**
 *
 */

#include <cctype>

using namespace std;

namespace cpps
{

const char* Token::TypeNames[] = {
        // *** Begin Miscelaneous Token Types *** //
        "TypeName",        // [a-zA-Z_]\w*
        "Identifier",      // \$[a-zA-Z_]\w*
        "StringLiteral",   // (['"]).*?(?<!\\)\1
        "NumericLiteral",  // (?:\d+|\d*\.\d+)d?
        "CommentLine",     // \/\/[^\n]*
        "CommentBlock",    // \/\*.*?\*\/
        "RegexMatch",      // \/.?(?<!\\)\/
        // *** End Miscelaneous Token Types *** //

        // *** Begin Non-Overloadable Operators *** //
        "Scope",           // ::
        "Semicolon",       // ;
        "Colon",           // :
        "Comma",           // ,
        "LogicalOr",       // \|\|
        "LogicalAnd",      // &&
        "TernaryIf",       // \?
        "OpenBrace",       // \{
        "CloseBrace",      // \}
        // *** End Non-Overloadable Operators *** //

        // *** Begin Overloadable Operators *** //
        "OpenParen",       // \(
        "CloseParen",      // \)
        "OpenBracket",     // \[
        "CloseBracket",    // \]
        "Equality",        // ==
        "NotEquality",     // !=
        "GreaterEqual",    // >=
        "LessEqual",       // <=
        "Assign",          // =
        "AssignPlus",      // \+=
        "AssignMinus",     // -=
        "AssignConcat",    // .=
        "AssignMultiply",  // \*=
        "AssignDivide",    // \/=
        "AssignModulo",    // %=
        "AssignBitAnd",    // &=
        "AssignBitXOr",    // \^=
        "AssignBitOr",     // |=
        "AssignLeftShift", // <<=
        "AssignRightShift",// >>=
        "RighShift",       // >>
        "LeftShift",       // <<
        "Increment",       // \+\+
        "Decrement",       // --
        "MemberAccess",    // ->
        "GreaterThan",     // >
        "LessThan",        // <
        "Plus",            // \+
        "Minus",           // -
        "Multiply",        // \*
        "Divide",          // \/
        "Modulo",          // %
        "Concat",          // \.
        "LogicalNot",      // !
        "BitwiseNot",      // ~
        "BitwiseAnd",      // &
        "BitwiseXOr",      // \^
        "BitwiseOr",       // \|
        // *** End Overloadable Operators *** //

        // *** Begin Keywords *** //
        "Break",           // break
        "Case",            // case
        "Catch",           // catch
        "Class",           // class
        "Const",           // const
        "Continue",        // continue
        "Default",         // default
        "Delete",          // delete
        "Do",              // do
        "Else",            // else
        "Enum",            // enum
        "False",           // false
        "For",             // for
        "Foreach",         // foreach
        "Friend",          // friend
        "Function",        // function
        "If",              // if
        "Include",         // include
        "InstanceOf",      // instanceof
        "Namespace",       // namespace
        "New",             // new
        "Null",            // null
        "Operator",        // operator
        "Private",         // private
        "Protected",       // protected
        "Public",          // public
        "Return",          // return
        "SizeOf",          // sizeof
        "Static",          // static
        "Struct",          // struct
        "Switch",          // switch
        "This",            // this
        "Throw",           // throw
        "True",            // true
        "Try",             // try
        "TypeDef",         // typedef
        "TypeNameOperator",// typename
        "Union",           // union
        "Using",           // using
        "While",           // while
        "Var",             // var
        // *** End Keywords *** //

        0 // End array
    };

const char* Token::_keywords[] = {
        "break",
        "case",
        "catch",
        "class",
        "const",
        "continue",
        "default",
        "delete",
        "do",
        "else",
        "enum",
        "false",
        "for",
        "foreach",
        "friend",
        "function",
        "if",
        "include",
        "instanceof",
        "namespace",
        "new",
        "null",
        "operator",
        "private",
        "protected",
        "public",
        "return",
        "sizeof",
        "static",
        "struct",
        "switch",
        "this",
        "throw",
        "true",
        "try",
        "typedef",
        "typename",
        "union",
        "using",
        "while",
        "var",

        0 // End array
    };

const char* Token::_operators[] = {
        
    };

Token::List Token::tokenize( const string& code )
{
    unsigned int lineCounter = 0;
    int codeLength = code.size();
    Token::List tokenList;

    for( int pos = 0; pos < codeLength; ++pos )
    {
        const char& thisC = code[pos];
        const char& nextC = pos+1 < codeLength ? code[pos+1] : 0;

        // Skip whitespace.
        if( isspace( thisC ) )
        {
            if( thisC == '\n' )
                ++lineCounter;
            continue;
        }

        // Next lets check for a keyword
        bool isKeyword = false;
        for( const char** mvr = Token::_keywords; !isKeyword && *mvr; ++mvr )
            if( Token::_matchKeyword( code, pos, *mvr ) )
            {
                isKeyword = true;
                tokenList.push_back( Token::_extractKeyword( code, pos, *mvr ) );
            }
        if( isKeyword )
            continue;

        // Are we starting a string literal? (StringLiteral)
        if( thisC == '\'' || thisC == '"' )
            tokenList.push_back( Token::_extractString( code, pos ) );

        // Or is this a single-line comment? (CommentLine)
        else if( thisC == '/' && nextC == '/' )
            Token::_extractCommentLine( code, pos );

        // Or is this a comment block? (CommentBlock)
        else if( thisC == '/' && nextC == '*' )
            Token::_extractCommentBlock( code, pos, lineCounter );

        // Or possibly a variable identifier? (Identifier)
        else if( thisC == '$' )
            tokenList.push_back( Token::_extractIdentifier( code, pos ) );

        // Or possibly a typename? (TypeName)
        else if( isalpha( thisC ) || thisC == '_' )
            tokenList.push_back( Token::_extractTypeName( code, pos ) );

        // Or a scope operator? (Scope)
        else if( thisC == ':' && nextC == ':' )
            tokenList.push_back( Token::_extractScope( code, pos ) );

        // Or a logical or? (LogicalOr)
        else if( thisC == '|' && nextC == '|' )
            tokenList.push_back( Token::_extractLogicalOr( code, pos ) );

        // Or a logical and? (LogicalAnd)
        else if( thisC == '&' && nextC == '&' )
            tokenList.push_back( Token::_extractLogicalAnd( code, pos ) );

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

        // Or is this a concatentation-assignment? (AssignConcat)
        else if( thisC == '.' && nextC == '=' )
            tokenList.push_back( Token::_extractAssignConcat( code, pos ) );

        // Or is this an equality check? (Equality)
        else if( thisC == '=' && nextC == '=' )
            tokenList.push_back( Token::_extractEquality( code, pos ) );

        // Or is this a not-equals check? (NotEquality)
        else if( thisC == '!' && nextC == '=' )
            tokenList.push_back( Token::_extractNotEquality( code, pos ) );

        // Or is this a greater-than-or-equal-to check? (GreaterEqual)
        else if( thisC == '>' && nextC == '=' )
            tokenList.push_back( Token::_extractGreaterEqual( code, pos ) );

        // Or is this a less-than-or-equal-to check? (LessEqual)
        else if( thisC == '<' && nextC == '=' )
            tokenList.push_back( Token::_extractLessEqual( code, pos ) );

        // Or is this a right shift? (RightShift)
        else if( thisC == '>' && nextC == '>' )
            tokenList.push_back( Token::_extractRightShift( code, pos ) );

        // Or is this a left shift? (LeftShift)
        else if( thisC == '<' && nextC == '<' )
            tokenList.push_back( Token::_extractLeftShift( code, pos ) );

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


bool Token::_matchKeyword(
        const string& code,
        const int&    pos,
        const char*   keyword
    )
{
    // First check the first two characters. This is really fast and will cut
    // out most tokens. We can only check the first two because "if" and "do"
    // are only two characters.
    if( code[pos] != keyword[0] || code[pos+1] == keyword[1] )
        return false;

    // First two characters match, now do the slightly more expensive substring
    // match and check the character after.
    const int   keywordSize = strlen(keyword);
    const char& charAfter   = code[ pos + keywordSize ];
    return code.substr( pos, keywordSize ) == keyword && // substring matches
          !isalnum( charAfter )                       && // char after is not alphanumeric
           charAfter != '_';                             // char after is not underscore
}


} // end namespace cpps
