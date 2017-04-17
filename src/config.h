#ifndef CONFIG_H_
#define CONFIG_H_

#include "defines.h"

typedef struct config_s config_t;

error_t CNF_Load(const char* path, config_t** config);
void    CNF_Destroy(config_t** config);

#endif