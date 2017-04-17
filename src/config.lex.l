%option noyywrap nomain yylineno

%x VALUE

%{
    #include "defines.h"
    #include "config.lex.h"

    char* key;
%}

ident       [a-zA-Z][a-zA-Z0-9_]{0,19}

%%
{ident}         { LOG("Identifier found %s\n", yytext); }
=               { BEGIN(VALUE); }
<VALUE>[^\n]*   { LOG("Value found %s\n", yytext); BEGIN(INITIAL); }
%%