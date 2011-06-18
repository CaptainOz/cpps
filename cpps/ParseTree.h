/**
 * @file
 *
 * @brief Describes the ParseTree class and its Node.
 *
 * @author Nate Lillich
 */

#ifndef __CPPS_PARSE_TREE_H_INCLUDED__
#define __CPPS_PARSE_TREE_H_INCLUDED__

#include <string>
#include <vector>

#include <Object.h>

namespace cpps
{

//! An abstract syntax tree model for holding compiled code statements.
class ParseTree
{
public:
    typedef std::vector< ParseTree::Node > StatementList;

    //! A syntax tree node for a single operation or value.
    class Node
    {
    public:
        virtual Scriptable::Reference getValue( Scriptable::Reference args ) = 0;

    }; // end class ParseTree::Node

private:
    StatementList statements;

public:
    ParseTree( void );

}; // end class ParseTree


/******************************************************************************/


//! This namespace contains all the ParseTree::Node subclasses.
namespace node
{

//! TypeName holds a reference to a class or function.
class TypeName : public ParseTree::Node
{
private:
    const std::string& typeNameStr;

public
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class TypeName


/******************************************************************************/


//! Variables holds a reference to a single variable.
class Variable : public ParseTree::Node
{
private:
    const std::string& variableName;

public
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class Variable


/******************************************************************************/


//! StringLiterals hold the value of a quoted string. They are like variables,
//! but unvarying.
class StringLiteral : public ParseTree::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class StringLiteral


/******************************************************************************/


//! CodeBlocks contain other statements to be executed.
class CodeBlock : public ParseTree::Node
{
private:
    const ParseTree::StatementList& statements;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class CodeBlock


/******************************************************************************/


//! UnaryOperators are any operator which take only one operand.
class UnaryOperator : public ParseTree::Node
{
private:
    const ParseTree::Node& operand;

protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        ) = 0;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class UnaryOperand


/******************************************************************************/


//! BinaryOperators are any operators which take two operands.
class BinaryOperator : public ParseTree::Node
{
private:
    const ParseTree::Node& leftOperand;
    const ParseTree::Node& rightOperand;

protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        ) = 0;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class BinaryOperator


/******************************************************************************/


//! TernaryOperators are any operators which take three operands.
class TernaryOperator : public ParseTree::Node
{
private:
    const ParseTree::Node& leftOperand;
    const ParseTree::Node& middleOperand;
    const ParseTree::Node& rightOperand;

protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& middleOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        ) = 0;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
}; // end class TernaryOperator


/******************************************************************************/


//! ScopeOperator resolves a reference to one within the given scope.
class ScopeOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

}; // end class ScopeOperator


/******************************************************************************/


//! LogicalOrOperator is true if either of its operands are true.
class LogicalOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

}; // end class LogicalOrOperator


/******************************************************************************/


//! LogicalAndOperator is true if both of its operands are true.
class LogicalAndOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

}; // end class LogicalAndOperator


/******************************************************************************/


//! InlineIfOperator acts like an if-then-else clause in only one statement.
class InlineIfOperator : public TernaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& middleOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );
}; // end class InlineIfOperator


/******************************************************************************/


//! FunctionOperator references another function by name.
class FunctionOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );
};


class TypecastOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class IndexOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class EqualityOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class NotEqualityOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class GreaterEqualOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class LessEqualOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignPlusOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignMinusOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignConcatOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignMultiplyOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignDivideOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignModuloOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignBitAndOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignBitXOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignBitOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignLeftShiftOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class AssignRightShiftOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class RightShiftOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class LeftShiftOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class PreIncrementOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class PostIncrementOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class PreDecrementOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class PostDecrementOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class MemberAccessOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class GreaterThanOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class LessThanOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class PlusOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class MinusOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class NegativeOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class MultiplyOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class DivideOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class ModuloOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class ConcatOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class LogicalNotOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class BitwiseNotOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class BitwiseAndOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class ReferenceOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );
};


class BitwiseXOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class BitwiseOrOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class BreakKeyword : public ParseTree::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
};


class ConstKeyword : public ParseTree::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
};


class ContinueKeyword : public ParseTree::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
};


class DeleteOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class IncludeOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class InstanceOfOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class NewOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class ReturnKeyword : public ParseTree::Node;
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
};


class SizeOfOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class ThrowOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class TypeDefOperator : public BinaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& leftOperand,
            const ParseTree::Node& rightOperand,
            Scriptable::Reference args
        );

};


class TypeNameOperator : public UnaryOperator
{
protected:
    virtual Scriptable::Reference operate(
            const ParseTree::Node& operand,
            Scriptable::Reference args
        );

};


class VarKeyword : public ParseTree::Node
{
private:
    const std::string& value;

public:
    virtual Scriptable::Reference getValue( Scriptable::Reference args );
};

} // end namespace node

} // emd namespace cpps

#endif // __CPPS_PARSE_TREE_H_INCLUDED__

