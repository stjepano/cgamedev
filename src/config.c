#include "config.h"

extern FILE* yyin;
extern int yylex();


error_t CNF_Load(const char* path, config_t** config)
{
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        return Error(CNF_ERR_CODE, "Could not open config file '%s'", path);
    }
    yyin = file;
    yylex();
    return NoError();
}

void CNF_Destroy(config_t** config)
{

}