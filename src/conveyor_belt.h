#ifndef __CONVEYOR_BELT_H__
#define __CONVEYOR_BELT_H__

#include <pthread.h>
#include "args.h"


/**
 * @brief Definição de constantes booleanas.
*/
#define FALSE                    0
#define TRUE                     1

/**
 * @brief Esteira de Sushi do Sushi Shop.
*/
typedef struct conveyor_belt {
    int _empty_slots;
    int _max_slots;
    int _belt_speed;
    pthread_t thread;
} conveyor_belt_t;

conveyor_belt_t* conveyor_belt_init(config_t* config);
void* conveyor_belt_run(void* arg);
void conveyor_belt_finalize(conveyor_belt_t* self);

void print_conveyor_belt(conveyor_belt_t* self);

#endif  //__CONVEYOR_BELT_H__
