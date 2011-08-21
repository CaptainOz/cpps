/**
 * @file
 *
 * @brief Contains the Token class description.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_TOKEN_H_INCLUDED__
#define __CPPS_TOKEN_H_INCLUDED__

#include <map>
#include <string>
#include <vector>

#include "Exceptions.h"
#include "ParserBase.h"
#include "Tokenizer.h"

namespace cpps
{

//! Class for the first-pass of parsing code.
/**
 * Each Token is an individual lexeme extracted from a source file. The public
 * static member Token::tokenize is a Token factory that generates tokens from
 * source code. It is the intended way to create Tokens.
 */
class Token
{
public:

    //! Enumeration of all possible token types.
    /**
     * @note
     * When updating this enumeration, also update the @c TypeNames, _keywords,
     * and _operators arrays defined in Token.cpp.
     *
     * These types are sorted by a combination of grouping and extraction order.
     * When adding or updating any token type make sure its regex match value
     * does not match the start of any of the types that follow it. For example,
     * LogicalOr (||) and AssignBitOr (|=) must both come before BitOr (|)
     * because BitOr starts both of them, however LogicalOr can come either
     * before or after AssignBitOr because neither is a substring of the other.
     *
     * @note
     * The tokens are listed in an order to optimize parsing by grouping tokens
     * by type and doing a single range comparision instead of many equality
     * tests. When adding new tokens, or updating old ones, be sure to include
     * it in the correct group.
     */
    enum Type
    {
    //  Token type          Regex to match

        // *** Begin Miscelaneous Token Types *** //
        TypeName,        // [a-zA-Z_]\w*
        Variable,        // \$[a-zA-Z_]\w*
        StringLiteral,   // (['"]).*?(?<!\\)\1
        NumericLiteral,  // (?i:[1-9]\d*|\d+\.\d*|0[0-7]*|0x[\da-f]+|0b[01]+)
        CommentLine,     // \/\/[^\n]*
        CommentBlock,    // \/\*.*?\*\/
        RegexMatch,      // \/.*(?<!\\)\/
        // *** End Miscelaneous Token Types *** //

        // *** Begin Non-Overloadable Operators *** //
        Scope,           // ::
        Semicolon,       // ;
        Colon,           // :
        Comma,           // ,

        LogicalOr,       // \|\|        Left associative binary operators
        LogicalAnd,      // &&

        TernaryIf,       // \?
        OpenBrace,       // \{
        CloseBrace,      // \}
        // *** End Non-Overloadable Operators *** //

        // *** Begin Overloadable Operators *** //
        OpenParen,       // \(
        CloseParen,      // \)
        OpenBracket,     // \[
        CloseBracket,    // \]

        Equality,        // ==          Left associative binary operators
        NotEquality,     // !=
        GreaterEqual,    // >=
        LessEqual,       // <=

        Assign,          // =           Right associative binary operators
        AssignPlus,      // \+=
        AssignMinus,     // -=
        AssignConcat,    // .=
        AssignMultiply,  // \*=
        AssignDivide,    // \/=
        AssignModulo,    // %=
        AssignBitAnd,    // &=
        AssignBitXOr,    // \^=
        AssignBitOr,     // \|=
        AssignLeftShift, // <<=
        AssignRightShift,// >>=

        Increment,       // \+\+        Either associative unary operators
        Decrement,       // --

        LogicalNot,      // !           Right associative unary operators
        BitwiseNot,      // ~

        RightShift,      // >>          Left associative binary operators
        LeftShift,       // <<
        MemberAccess,    // ->
        GreaterThan,     // >
        LessThan,        // <
        Plus,            // \+
        Minus,           // -
        Multiply,        // \*
        Divide,          // \/
        Modulo,          // %
        Concat,          // \.
        BitwiseAnd,      // &
        BitwiseXOr,      // \^
        BitwiseOr,       // \|
        // *** End Overloadable Operators *** //

        // *** Begin Keywords *** //
        Break,           // break
        Case,            // case
        Catch,           // catch
        Class,           // class
        Const,           // const
        Continue,        // continue
        Default,         // default
        Delete,          // delete
        Do,              // do
        Else,            // else
        Enum,            // enum
        False,           // false
        For,             // for
        Foreach,         // foreach
        Friend,          // friend
        Function,        // function
        If,              // if
        Include,         // include
        InstanceOf,      // instanceof
        Namespace,       // namespace
        New,             // new
        Null,            // null
        Operator,        // operator
        Private,         // private
        Protected,       // protected
        Public,          // public
        Return,          // return
        SizeOf,          // sizeof
        Static,          // static
        Struct,          // struct
        Switch,          // switch
        This,            // this
        Throw,           // throw
        True,            // true
        Try,             // try
        TypeDef,         // typedef
        TypeNameOperator,// typename
        Union,           // union
        Using,           // using
        While,           // while
        Var,             // var
        // *** End Keywords *** //

        EndOfFile,
        TokenTypeCount
    }; // end Token::Type

    //! Array of token type-names suitable for human consumption.
    static const char* TypeNames[];

    //! A list of tokens as generated by the Token::tokenize static method.
    typedef std::vector<Token> List;

    //! Returns the type of this token.
    /**
     * @return The Token::Type of this token.
     */
    const Token::Type& getType( void ) const;

    //! Returns the string version of the token's type.
    /**
     * @return The string name of the this token's type.
     */
    const std::string getTypeString( void ) const;

    //! Returns the string as extracted from the code.
    /**
     * @return The string from the code.
     */
    const std::string getString( void ) const;

    //! Returns the line number the token was extracted from.
    /**
     * @return The line number the token was extracted from.
     */
    const unsigned int& getLineNumber( void ) const;

    //! Returns true if this token is for an operator.
    bool isOperator( void ) const;

    //! Returns true if this token is for a keyword.
    bool isKeyword( void ) const;

    //! Returns the name of the token type.
    /**
     * @param type The type to get the name of.
     *
     * @return The name of the provided token type.
     */
    static const std::string getTypeString( const Token::Type& type );

private:
    std::string  m_tokenStr;
    Token::Type  m_type;
    unsigned int m_lineNumber;

    friend class Tokenizer;

    //! Array of keyword strings as they should appear in the code.
    static const char* _keywords[];

    //! Array of operator strings as they should appear in the code.
    static const char* _operators[];

    static const std::map< Token::Type, ParserBase::Tokens__ > _conversion;

    //! Private token constructor used by Tokenizer.
    /**
     * @param type          The type of token this is.
     * @param lineNumber    The line number the token was extracted from.
     * @param tokenStr      The extract string taken from the source file.
     *
     * @note The @p tokenStr is only required for TypeName, Variable,
     *       StringLiteral, and NumericLiteral tokens. All other token types
     *       have well-defined representations.
     */
    Token(
            const Token::Type&  type,
            const unsigned int& lineNumber,
            const std::string&  tokenStr = ""
        ) throw();

public:
    Token( const Token& other ) throw();

}; // end class Token


/******************************************************************************/


inline Token::Token(
        const Token::Type&  type,
        const unsigned int& lineNumber,
        const std::string&       tokenStr
    ) throw()
    : m_tokenStr( tokenStr ),
      m_type( type ),
      m_lineNumber( lineNumber )
{
}


inline Token::Token( const Token& other ) throw()
    : m_tokenStr( other.m_tokenStr ),
      m_type( other.m_type ),
      m_lineNumber( other.m_lineNumber )
{
}


/******************************************************************************/


inline const Token::Type& Token::getType( void ) const
{
    return m_type;
}


/******************************************************************************/


inline const std::string Token::getTypeString( void ) const
{
    return getTypeString( getType() );
}


/******************************************************************************/


inline const std::string Token::getTypeString( const Token::Type& type )
{
    return Token::TypeNames[ type ];
}


/******************************************************************************/


inline const std::string Token::getString( void ) const
{
    const Token::Type& type = getType();
    return isOperator() ? Token::_operators[ ((int)type) - Token::Scope ] :
           isKeyword()  ? Token::_keywords[  ((int)type) - Token::Break ]  :
                          m_tokenStr                 ;
}


/******************************************************************************/


inline const unsigned int& Token::getLineNumber( void ) const
{
    return m_lineNumber;
}


/******************************************************************************/


inline bool Token::isOperator( void ) const
{
    const Token::Type& type = getType();
    return type >= Token::Scope && type <= Token::BitwiseOr;
}


/******************************************************************************/


inline bool Token::isKeyword( void ) const
{
    const Token::Type& type = getType();
    return type >= Token::Break && type <= Token::Var;
}


} // end namespace cpps

#endif // __CPPS_TOKEN_H_INCLUDED__

