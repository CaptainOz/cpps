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
        "break",      "case",      "catch",  "class",    "const",    "continue",
        "default",    "delete",    "do",     "else",     "enum",     "false",
        "for",        "foreach",   "friend", "function", "if",       "include",
        "instanceof", "namespace", "new",    "null",     "operator", "private",
        "protected",  "public",    "return", "sizeof",   "static",   "struct",
        "switch",     "this",      "throw",  "true",     "try",      "typedef",
        "typename",   "union",     "using",  "while",    "var",

        0 // End array
    };

const char* Token::_operators[] = {
        "::",  ";",   ":",  ",",  "||", "&&", "?",  "{",  "}",
        "(",   ")",   "[",  "]",  "==", "!=", ">=", "<=", "=",
        "+=",  "-=",  ".=", "*=", "/=", "%=", "&=", "^=", "|=",
        "<<=", ">>=", ">>", "<<", "++", "--", "->", ">",  "<",
        "+",   "-",   "*",  "/",  "%",  ".",  "!",  "~",  "&",
        "^",   "|",

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

        // Skip whitespace.
        if( isspace( thisC ) )
        {
            if( thisC == '\n' )
                ++lineCounter;
            continue;
        }

        // Set up the additional variables we'll need.
        const char& nextC = pos+1 < codeLength ? code[pos+1] : 0;
        bool tokenized = true;

        // Are we starting a string literal? (StringLiteral)
        if( thisC == '\'' || thisC == '"' )
            tokenList.push_back( Token::_extractString( code, pos ) );

        // Or is this a numeric literal? (NumericLiteral)
        else if( isdigit( thisC ) || (thisC == '.' && isdigit( nextC ) )
            tokenList.push_back( Token::_extractNumber( code, pos ) );

        // Or is this a variable identifier? (Identifier)
        else if( thisC == '$' )
            tokenList.push_back( Token::_extractIdentifier( code, pos ) );

        // Or is this a one-line comment? (CommentLine)
        else if( thisC == '/' && nextC == '/' )
            Token::_extractCommentLine( code, pos );

        // Or is this a comment block? (CommentBlock)
        else if( thisC == '/' && nextC == '*' )
            Token::_extractCommentBlock( code, pos );

        // Otherwise we haven't tokenized it yet, so set
        else
            tokenized = false;

        // Next lets check for a keyword
        for( const char** mvr = Token::_keywords; !tokenized && *mvr; ++mvr )
            if( Token::_matchKeyword( code, pos, *mvr ) )
            {
                tokenized = true;
                tokenList.push_back( Token::_extractKeyword( code, pos, *mvr ) );
            }

        // Next lets check for an operator.
        for( const char** mvr = Token::_operators; !tokenized && *mvr; ++mvr )
            if( Token::_matchToken( code, pos, *mvr ) )
            {
                tokenized = true;
                tokenList.push_back( Token::_extractToken( code, pos, *mvr ) );
            }

        // If we still haven't tokenized the string yet, lets see if its a
        // typename (i.e. class name, function name, etc).
        if( !tokenized && isalpha( thisC ) || thisC == '_' )
        {
            tokenized = true;
            tokenList.push_back( Token::_extractIdentifier( code, pos ) );
        }

        // Still haven't tokenized it!? Must be an error.
        if( !tokenized )
            throw ParseException(
                    ParseException::UnknownToken,   // Exception type
                    code,                           // Erroneous code string
                    pos,                            // Position in string
                    lineCounter                     // Line number of error
                );
    }
}


/******************************************************************************/


bool Token::_matchKeyword(
        const string& code,
        const int&    pos,
        const char*   keyword
    )
{
    // Does the token match the keyword?
    if( !Token::_matchToken( code, pos, keyword ) )
        return false;

    // The string matches the keyword, but is it the whole word? It could be the
    // start of another (i.e. newFooBar).
    const char& charAfter   = code[ pos + strlen(keyword) ];
    return !isalnum( charAfter ) && // char after is not alphanumeric
            charAfter != '_';       // char after is not underscore
}


/******************************************************************************/


bool Token::_matchToken( const string& code, const int& pos, const char* token )
{
    // Loop through the string to find a non-matching character.
    codeLength = code.size();
    for( int i = 0; token[i] && pos+i < codeLength; ++i )
        if( code[ pos+i ] != token[i] )
            return false;

    // We didn't find a non-matching character, but did we get through the whole
    // token? (remaining code could be shorter than token length.)
    return token[i] == 0;
}


} // end namespace cpps
