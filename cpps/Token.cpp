/**
 *
 */

#include <cctype>
#include "Token.h"

using namespace std;

namespace cpps
{

// Token typenames as suitable for humans to read ordered same as Token::Type.
const char* Token::TypeNames[] = {
        // *** Begin Miscelaneous Token Types *** //
        "TypeName",        // [a-zA-Z_]\w*
        "Variable",        // \$[a-zA-Z_]\w*
        "StringLiteral",   // (['"]).*?(?<!\\)\1
        "NumericLiteral",  // (?i:[1-9]\d*|\d+\.\d*|0[0-7]*|0x[\da-f]+|0b[01]+)
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

// Keyword strings as they appear in the code ordered the same as Token::Type.
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

// Operator strings as they appear in the code ordered the same as Token::Type.
const char* Token::_operators[] = {
        "::",  ";",   ":",  ",",  "||", "&&", "?",  "{",  "}",
        "(",   ")",   "[",  "]",  "==", "!=", ">=", "<=", "=",
        "+=",  "-=",  ".=", "*=", "/=", "%=", "&=", "^=", "|=",
        "<<=", ">>=", ">>", "<<", "++", "--", "->", ">",  "<",
        "+",   "-",   "*",  "/",  "%",  ".",  "!",  "~",  "&",
        "^",   "|",

        0 // End array
    };

Token::List Token::tokenize( const string& code ) throw( ParseException )
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
            tokenList.push_back( Token::_extractString( code, pos, lineCounter ) );

        // Or is this a numeric literal? (NumericLiteral)
        else if( isdigit( thisC ) )
            tokenList.push_back( Token::_extractNumber( code, pos, lineCounter ) );

        // Or is this a variable identifier? (Identifier)
        else if( thisC == '$' )
            tokenList.push_back( Token::_extractIdentifier( code, pos, lineCounter ) );

        // Or is this a one-line comment? (CommentLine)
        else if( thisC == '/' && nextC == '/' )
            Token::_extractCommentLine( code, pos, lineCounter );

        // Or is this a comment block? (CommentBlock)
        else if( thisC == '/' && nextC == '*' )
            Token::_extractCommentBlock( code, pos, lineCounter );

        // Otherwise we haven't tokenized it yet, so set the tokenized flag
        else
            tokenized = false;

        // Next lets check for a keyword
        for( const char** mvr = Token::_keywords; !tokenized && *mvr; ++mvr )
            if( Token::_matchKeyword( code, pos, *mvr ) )
            {
                tokenized = true;
                const Token& token = Token::_extractKeyword(
                        code,
                        pos,
                        mvr - Token::_keywords,
                        lineCounter
                    );
                tokenList.push_back( token );
            }

        // Next lets check for an operator.
        for( const char** mvr = Token::_operators; !tokenized && *mvr; ++mvr )
            if( Token::_matchToken( code, pos, *mvr ) )
            {
                tokenized = true;
                const Token& token = Token::_extractOperator(
                        code,
                        pos,
                        mvr - Token::_operators,
                        lineCounter
                    );
                tokenList.push_back( token );
            }

        // If we still haven't tokenized the string yet, lets see if its a
        // typename (i.e. class name, function name, etc).
        if( !tokenized && isalpha( thisC ) || thisC == '_' )
        {
            tokenized = true;
            tokenList.push_back( Token::_extractIdentifier( code, pos, lineCounter ) );
        }

        // Still haven't tokenized it!? Must be an error.
        // TODO: Create ParseException class.
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
    ) throw()
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
    throw()
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


/******************************************************************************/


Token Token::_extractString(
        const string&       code,
              int&          pos,
        const unsigned int& lineNumber
    ) throw( ParseException )
{
    // Loop through the string pulling out each character until we find the
    // closing quote.
    string tokenStr;
    const char& openQuote = code[ pos ];
    const int& codeLength = code.size();
    for( ++pos; code[ pos ] != openQuote; ++pos )
    {
        // Copy the character.
        const char& c = code[ pos ];
        tokenStr += c;

        // Check that we are still within range and the line hasn't ended.
        if( pos >= codeLength || c == '\n' )
            throw ParseException(
                    ParseException::UnexpectedToken,
                    code,
                    pos,
                    lineNumber,
                    "Unclosed string literal."
                );

        // If this char is an escaper, prematurely jump to and grab the next one
        // but only if we aren't escaping a newline (those aren't allowed in
        // strings!).
        if( c == '\\' && code[ pos + 1 ] != '\n' )
            tokenStr += code[ ++pos ];
    }

    // Create and return a new token.
    return Token( Token::StringLiteral, lineNumber, tokenStr );
}


/******************************************************************************/


Token Token::_extractNumber(
        const string&       code,
              int&          pos,
        const unsigned int& lineNumber
    ) throw( ParseException )
{
    enum NumberBase {
        nb_Binary,
        nb_Octal,
        nb_Decimal,
        nb_Hex
    }

    // First lets figure out what kind of digit string this is. This will be
    // used further down while extracting to ensure valid characters.
    int type;
    const char& nextC = code[pos+1];
    string tokenStr;
    if( code[pos] != '0' || nextC == '.' )
        type = nb_Decimal;
    else if( nextC == 'b' || nextC == 'B' )
    {
        type = nb_Binary;
        tokenStr += "0b";
        pos += 2;
    }
    else if( nextC == 'x' || nextC == 'X' )
    {
        type = nb_Hex;
        tokenStr += "0x";
        pos += 2;
    }
    else
        type = nb_Octal;

    // Extract all the digits
    bool decimalIncluded = false;
    const int codeLength = code.size();
    for( char c = tolower(code[pos]);
         pos < codeLength       &&
        (isdigit(c)             ||
         c == '.'               ||
         (c <= 'f' && c >= 'a')  );
         c = tolower(code[++pos]) )
    {
        if( (c == '.' && type != nb_Decimal)            || // Only decimal has decimal points
            (c != '.' && !isdigit(c) && type != nb_Hex) || // Only hex has non-digit chars
            (c >  '7' && type == nb_Octal)              || // Octal must be between 0 and 7
            (c >  '1' && type == nb_Binary)              ) // Binary must be 0 or 1
            throw ParseException(
                    ParseException::UnexpectedToken,
                    code,
                    pos,
                    lineNumber,
                    "Invalid character in numeric literal."
                );

        // If we've come across another decimal place and we've already included
        // a decimal place, break the loop here.
        if( decimalIncluded && c == '.' )
            break;

        // Extract the character and update the decimalIncluded flag.
        tokenStr += c;
        decimalIncluded = decimalIncluded || c == '.';
    }

    // Create and return a new token.
    return Token( Token::NumericLiteral, lineNumber, tokenStr );
}


/******************************************************************************/


Token Token::_extractIdentifier(
        const std::string&  code,
              int&          pos,
        const unsigned int& lineNumber
    ) throw( ParseException )
{
    // What type of identifier are we extracting?
    Token::Type tokenType;
    if( code[pos] == '$' )
    {
        tokenType = Token::Variable;
        ++pos;
    }
    else
        tokenType = Token::TypeName;

    // Check that the first character after the $ is valid.
    if( !isalpha( code[pos] ) && code[pos] != '_' )
        throw ParseException(
                ParseException::InvalidName,
                code,
                pos,
                lineNumber,
                "Variable names must start with an alphabetic character."
            );

    // Now extract the identifier's name
    string tokenStr;
    const int codeLength = code.size();
    for( char c = code[ pos ];
         pos < codeLength && isalnum( c ) || c == '_';
         c = code[ ++pos ] )
        tokenStr += c;

    // Create and return a new token.
    return Token( tokenType, lineNumber, tokenStr );
}


/******************************************************************************/


void Token::_extractCommentLine(
        const std::string&  code,
              int&          pos,
        const unsigned int& lineNumber
    ) throw()
{
    // Comment lines end at the new-line.
    const int codeLength = code.size();
    while( ++pos < codeLength && code[ pos ] != '\n' )
        ; // Do nothing in the loop
}


/******************************************************************************/


void Token::_extractCommentBlock(
        const std::string&  code,
              int&          pos,
              unsigned int& lineNumber
    ) throw( ParseException )
{
    const int codeLength = code.size();
    pos += 2;
    for( char c = code[ pos ]; !(c == '*' && c == '/'); c = code[ ++pos ] )
    {
        // Make sure we haven't reached the end of the code before the comment
        // was closed.
        if( pos >= codeLength )
            throw ParseException(
                    ParseException::UnexpectedToken,
                    code,
                    pos,
                    lineNumber,
                    "Unclosed block comment."
                );

        // Be sure to count up the lines within the comment
        if( c == '\n' )
            ++lineNumber;
    }
}


/******************************************************************************/


Token Token::_extractKeyword(
        const std::string&  code,
              int&          pos,
        const int&          keywordIndex,
        const unsigned int& lineNumber
    ) throw()
{
    // Calculate the token type and move the position up
    const Token::Type tokenType = (Token::Type)((int)Token::Break + keywordIndex);
    pos += strlen( Token::_keywords[ keywordIndex ] );
    return Token( tokenType, lineNumber );
}


/******************************************************************************/


Token Token::_extractOperator(
        const std::string&  code,
              int&          pos,
        const int&          operatorIndex,
        const unsigned int& lineNumber
    ) throw()
{
    // Calculate the token type and move the position up
    const Token::Type tokenType = (Token::Type)((int)Token::Scope + operatorIndex);
    pos += strlen( Token::_operators[ operatorIndex ] );
    return Token( tokenType, lineNumber );
}


/******************************************************************************/


Token::Token(
        const Token::Type& type,
        const unsigned int& lineNumber,
        const string& tokenStr
    ) throw()
    : mType( type ),
      mLineNumber( lineNumber ),
      mTokenStr( tokenStr )
{
}


} // end namespace cpps

