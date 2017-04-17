%option noyywrap nomain yylineno

%x VALUE
%x QVALUE

%{
    #include "defines.h"
    #include "config.lex.h"

    #include "strutils.h"

    char* key;
%}

ident       [a-zA-Z][a-zA-Z0-9_]{0,19}

%%
\n              { }
[ \t]           { }
#.*             { }
{ident}         { key = STR_strdup(yytext); }
[ \t]*=[ \t]*   { BEGIN(VALUE); }
[ \t]*=[ \t]*["]   { BEGIN(QVALUE); }
<VALUE>[^ \t#\n]*  { LOG("key: '%s', value: '%s'\n", key, yytext); free(key); BEGIN(INITIAL); }
<QVALUE>[^"]* { LOG("key: '%s', value: '%s'\n", key, yytext); free(key); }
<QVALUE>["]   { BEGIN(INITIAL); }
%%