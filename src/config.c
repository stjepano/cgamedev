#include "config.h"
#include "config.lex.h"
#include "strutils.h"
#include <string.h>

extern FILE* yyin;
extern int yylex();
extern cnf_keyval_t* cnf_keyvals_head;

#define CNF_ERR_CODE 267

typedef struct config_s {
    cnf_keyval_t* head;
} config_t;


static cnf_keyval_t* FindNode(const config_t* config, const char* key);

error_t CNF_Load(const char* path, config_t** config)
{
    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        return Error(CNF_ERR_CODE, "Could not open config file '%s'", path);
    }
    yyin = file;
    yylex();

    config_t* cnf = (config_t*) malloc(sizeof(config_t));
    cnf->head = cnf_keyvals_head;

    *config = cnf;

    return NoError();
}

void CNF_Destroy(config_t** config)
{
    if (config == NULL) return;
    config_t* cnf = (*config);
    if (cnf == NULL) return;

    cnf_keyval_t *it=cnf->head, *tmp = NULL;
    while (it != NULL)
    {
        tmp = it->next;
        FREE(it->key);
        FREE(it->value);
        FREE(it);
        it = tmp;
    }

    FREE(cnf);
    *config = NULL;
}


void CNF_Visit(const config_t* config, cnf_visit_f visit_f)
{
    if (config == NULL) return;
    cnf_keyval_t* it = config->head;
    while (it != NULL)
    {
        visit_f(it->key, it->value);
        it = it->next;
    }
}

bool CNF_Has(const config_t* config, const char* key)
{
    return FindNode(config, key) != NULL;
}

const char* CNF_Get(const config_t* config, const char* key)
{
    return CNF_GetD(config, key, NULL);
}

const char* CNF_GetD(const config_t* config, const char* key, const char* dval)
{
    cnf_keyval_t* node = FindNode(config, key);
    return (node != NULL)?node->value:dval;
}

static cnf_keyval_t* FindNode(const config_t* config, const char* key)
{
    if (ISNULL(config)) return NULL;
    cnf_keyval_t* it = config->head;
    while (it != NULL)
    {
        if (strcmp(it->key, key) == 0)
        {
            break;
        }
        it = it->next;
    }
    return it;
}


#define DEFAULT_RESOLUTION "1024x768"
#define DEFAULT_FULLSCREEN "false"
#define DEFAULT_TITLE "Demo 01"

error_t CNF_LoadDisplayConfig(const config_t* config, display_config_t* out)
{
    const char* resolution_str = CNF_GetD(config, "DPY_RESOLUTION", DEFAULT_RESOLUTION);
    if (FAILED(STR_ParseResolution(resolution_str, &out->width, &out->height)))
    {
        return Error(CNF_ERR_CODE, "Error parsing resolution: %s", GetError());
    }
    const char* fullscreen_str = CNF_GetD(config, "DPY_FULLSCREEN", DEFAULT_FULLSCREEN);
    if (stricmp(fullscreen_str, "true") == 0)
    {
        out->fullscreen = true;
    }
    out->title = CNF_GetD(config, "DPY_TITLE", DEFAULT_TITLE);
    LOG("Load display config: width=%d, height=%d, fullscreen=%d, title=%s\n", out->width, out->height, out->fullscreen, out->title);
    return NoError();
}