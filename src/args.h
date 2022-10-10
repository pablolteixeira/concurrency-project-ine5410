#ifndef __ARGS_H__
#define __ARGS_H__

#include <stdio.h>


/**
 * @brief Configuração para uma simulação.
*/
typedef struct config {
    unsigned int students;
    unsigned int buffets;
    unsigned int tables;
    unsigned int seat_per_table;
} config_t;

extern config_t config;


/**
 * @brief Função para captura da configuração de entrada.
*/
config_t parse(int argc, char** argv);


#endif  // __ARGS_H__
