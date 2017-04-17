#ifndef CONFIG_H_
#define CONFIG_H_

#include "defines.h"

typedef struct config_s config_t;

error_t CNF_Load(const char* path, config_t** config);
void    CNF_Destroy(config_t** config);

typedef void (*cnf_visit_f)(const char* key, const char* value);

void CNF_Visit(const config_t* config, cnf_visit_f visit_f);

bool CNF_Has(const config_t* config, const char* key);
const char* CNF_Get(const config_t* config, const char* key);
const char* CNF_GetD(const config_t* config, const char* key, const char* dval);

#endif