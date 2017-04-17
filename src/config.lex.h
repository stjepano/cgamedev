#ifndef CONFIG_LEX_H_
#define CONFIG_LEX_H_

typedef struct cnf_keyval_s
{
    char* key;
    char* value;
    int lineno;
    struct cnf_keyval_s* next;
} cnf_keyval_t;

#endif