#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <pthread.h>

#include "args.h"


/**
 * @brief Definição de constantes booleanas.
*/
#define FALSE                    0
#define TRUE                     1

/**
 * @brief Definição de unidades de tempo úteis para o relógio virtual.
*/
#define DAY                      86400
#define HOUR                     3600
#define MINUTE                   60

/**
 * @brief Relógio virtual para simulação.
*/
typedef struct virtual_clock {
    pthread_t thread;
    unsigned int clock_speed_multiplier;
    unsigned int opening_time;
    unsigned int closing_time;
    unsigned int current_time;
} virtual_clock_t;

/**
 * @brief Sleep for the specified amount of milisseconds.
*/
int msleep(long msec);

void* clock_run(void* data);
void clock_init(virtual_clock_t* self, config_t* config);
void clock_finalize(virtual_clock_t* self);
unsigned int read_minutes(unsigned int value);
unsigned int read_hours(unsigned int value);
unsigned int read_seconds(unsigned int value);
void read_clock(virtual_clock_t* self);

#endif  // __CLOCK_H__
