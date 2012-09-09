
#pragma once

#include <cstdarg>
#include <iostream>

namespace type {
    enum Type {
        CONSTANT,
        IDENTIFIER,
        OPERATOR
    };
}

namespace node {
    struct Node;

    struct Constant {
        int value;
    };

    struct Identifier {
        char index;
    };

    struct Operator {
        int     operatorId;
        int     operandCount;
        Node**  operands;
    };

    struct Node {
        type::Type type;
        union {
            Constant    constant;
            Identifier  identifier;
            Operator    operatr;
        };

        Node( const int operatorId, const int operandCount, ... ):
            type( type::OPERATOR )
        {
            operatr.operatorId      = operatorId;
            operatr.operandCount    = operandCount;
            operatr.operands        = new Node*[ operandCount ];

            va_list args;
            va_start( args, operandCount );
            for( int i = 0; i < operandCount; ++i ){
                operatr.operands[ i ] = va_arg( args, Node* );
            }
            va_end( args );
        }

        Node( const char _identifer ):
            type( type::IDENTIFIER )
        {
            identifier.index = _identifer;
        }

        Node( const int value ):
            type( type::CONSTANT )
        {
            constant.value = value;
        }

        ~Node( void ){
            if( type == type::OPERATOR ){
                for( int i = 0; i < operatr.operandCount; ++i ){
                    delete operatr.operands[ i ];
                }
                delete[] operatr.operands;
            }
        }
    };

}

extern int symbols[ 'z' - 'a' ];

class LexerContext {
private:
    void initScanner( void );
    void destroyScanner( void );

public:
    void* scanner;
    int result;
    std::istream* is;

    LexerContext( std::istream* _is = &std::cin ): is( _is ){
        initScanner();
    }

    ~LexerContext( void ){
        destroyScanner();
    }
};
