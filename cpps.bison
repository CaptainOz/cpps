%baseclass-preinclude cmath
%stype double

%token NUM
%left  '-' '+'
%left  '*' '/'
%right '^'

%%

input:
    // empty
|
    input line
;

line:
    ';'
|
    exp ';'
    {
        std::cout << "    " << $1 << std::endl;
    }
;

exp:
    NUM
|
    exp '+' exp
    {
        $$ = $1 + $3;
    }
|
    exp '-' exp
    {
        $$ = $1 - $3;
    }
|
    exp '*' exp
    {
        $$ = $1 * $3;
    }
|
    exp '/' exp
    {
        $$ = $1 / $3;
    }
|
    exp '^' exp
    {
        $$ = std::pow( $1, $3 );
    }
|
    '-' exp
    {
        $$ = -$2;
    }
;
