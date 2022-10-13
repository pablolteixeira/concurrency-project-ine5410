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
    pthread_cond_t closing_time_cond_var;
    unsigned int clock_speed_multiplier;
    unsigned int opening_time;
    unsigned int closing_time;
    unsigned int current_time;
} virtual_clock_t;

/**
 * @brief Sleep for the specified amount of milisseconds.
*/
int msleep(long msec);

virtual_clock_t* virtual_clock_init(config_t* config);
void* virtual_clock_run(void* arg);
void virtual_clock_finalize(virtual_clock_t* self);

unsigned int read_minutes(unsigned int value);
unsigned int read_hours(unsigned int value);
unsigned int read_seconds(unsigned int value);
void print_current_virtual_time(virtual_clock_t* self);

#endif  // __CLOCK_H__
