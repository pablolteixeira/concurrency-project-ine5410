#ifndef __CLOCK_H__
#define __CLOCK_H__

#include <pthread.h>

/**
 * @brief Definição de constantes booleanas.
*/
#define FALSE                    0
#define TRUE                     1

/**
 * @brief Configurações de relógio virtual.
*/
#define CLOCK_SPEED_MULTIPLIER   60
#define STOP_TIME                18

/**
 * @brief Relógio virtual para simulação.
*/
typedef struct virtual_clock {
    pthread_t thread;
    unsigned int value;
} virtual_clock_t;

/**
 * @brief Sleep for the specified amount of milisseconds.
*/
int msleep(long msec);

void* clock_run();
void clock_init(virtual_clock_t* self);
void clock_finalize(virtual_clock_t *self);
int read_minutes(unsigned int clock_value);
int read_hours(unsigned int clock_value);
void read_clock();

#endif  // __CLOCK_H__
