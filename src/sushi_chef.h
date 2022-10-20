#ifndef __SUSHI_CHEF_H__
#define __SUSHI_CHEF_H__

#include <pthread.h>
#include "args.h"
#include "menu.h"
#include "conveyor_belt.h"


/**
 * @brief Estrutura encapsulando um Sushi chef.
*/
typedef struct sushi_chef {
    int _id;
    int _seat_position;
    pthread_t thread;
} sushi_chef_t;

void seat_at_conveyor_slot(sushi_chef_t* self, conveyor_belt_t* conveyor);
void sushi_chef_leave_seat(sushi_chef_t* self, conveyor_belt_t* conveyor);
void sushi_chef_place_food(sushi_chef_t* self, enum menu_item dish);
void sushi_chef_prepare_food(sushi_chef_t* self, enum menu_item menu_item);

sushi_chef_t* sushi_chef_init();
void* sushi_chef_run(void* arg);
void sushi_chef_finalize(sushi_chef_t* self);

void print_sushi_chef(sushi_chef_t* self);

#endif  // __SUSHI_CHEF_H__
