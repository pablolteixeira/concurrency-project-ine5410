#ifndef __SUSHI_CHEF_H__
#define __SUSHI_CHEF_H__

#include <pthread.h>
#include "args.h"


/**
 * @brief Definição de constantes booleanas.
*/
#define FALSE                    0
#define TRUE                     1

/**
 * @brief Definição de constantes úteis para os clientes do Sushi shop.
*/
#define NOT_SEATED               -1

/**
 * @brief Estrutura encapsulando um Sushi chef.
*/
typedef struct sushi_chef {
    int _id;
    int _seat_position;
    int _preparation_speed;
    pthread_t thread;
} sushi_chef_t;

sushi_chef_t* sushi_chef_init(int seat_position, int preparation_speed);
void* sushi_chef_run(void* arg);
void sushi_chef_finalize(sushi_chef_t* self);

#endif  // __SUSHI_CHEF_H__
