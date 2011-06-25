%baseclass-preinclude cmath

%token NUM
%stype double

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
    exp exp '+'
    {
        $$ = $1 + $2;
    }
|
    exp exp '-'
    {
        $$ = $1 - $2;
    }
|
    exp exp '*'
    {
        $$ = $1 * $2;
    }
|
    exp exp '/'
    {
        $$ = $1 / $2;
    }
|
    exp exp '^'
    {
        $$ = std::pow( $1, $2 );
    }
|
    exp 'n'
    {
        $$ = -$1;
    }
;
