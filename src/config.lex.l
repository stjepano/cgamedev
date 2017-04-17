%option noyywrap nomain yylineno

%x VALUE
%x QVALUE

%{
    #include "defines.h"
    #include "config.lex.h"

    #include "strutils.h"

    char* key;

    cnf_keyval_t* cnf_keyvals_head = NULL;
    static void AddNode();
%}

ident       [a-zA-Z][a-zA-Z0-9_]*

%%
\n              { }
[ \t]           { }
#.*             { }
{ident}         { key = STR_strdup(yytext); }
[ \t]*=[ \t]*   { BEGIN(VALUE); }
[ \t]*=[ \t]*["]   { BEGIN(QVALUE); }
<VALUE>[^ \t#\n]*  { AddNode(); BEGIN(INITIAL); }
<QVALUE>[^"]* { AddNode(); }
<QVALUE>["]   { BEGIN(INITIAL); }
%%


static void AddNode()
{
    // try to find node with same name
    cnf_keyval_t* it = cnf_keyvals_head;
    cnf_keyval_t* tail = NULL;
    while (it != NULL)
    {
        if (strcmp(it->key, key) == 0)
        {
            // replace value and lineno
            free(it->value);
            it->value = STR_strdup(yytext);
            it->lineno = yylineno;
            return;
        }
        tail = it;
        it = it->next;
    }

    cnf_keyval_t* newkeyval = (cnf_keyval_t*) malloc(sizeof(cnf_keyval_t));
    newkeyval->next = NULL;
    newkeyval->key = key;
    newkeyval->value = STR_strdup(yytext);
    newkeyval->lineno = yylineno;

    if (tail == NULL)
    {
        cnf_keyvals_head = newkeyval;
    }
    else
    {
        tail->next = newkeyval;
    }
}