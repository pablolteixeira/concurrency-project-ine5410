#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <semaphore.h>
#include "conveyor_belt.h"
#include "virtual_clock.h"
#include "queue.h"
#include <semaphore.h>

/**
 * @brief Inicia um relógio virtual (de modo global)
 * 
 * @param virtual_clock 
 */
extern void globals_set_virtual_clock(virtual_clock_t *virtual_clock);

/**
 * @brief Retorna um relógio virtual (de modo global)
 * 
 * @return virtual_clock_t* 
 */
extern virtual_clock_t *globals_get_virtual_clock();

/**
 * @brief Inicia uma esteira de sushi (de modo global).
 * 
 * @param conveyor_belt
 */
extern void globals_set_conveyor_belt(conveyor_belt_t *conveyor_belt);

/**
 * @brief Retorna uma esteira de sushi (de modo global)
 * 
 * @return conveyor_belt_t* 
 */
extern conveyor_belt_t *globals_get_conveyor_belt();

/**
 * @brief Inicia uma fila (de modo global)
 * 
 * @param queue 
 */
extern void globals_set_queue(queue_t *queue);

/**
 * @brief Retorna uma fila (de modo global)
 * 
 * @return queue_t* 
 */
extern queue_t *globals_get_queue();

/**

 * @brief Retorna um empty_slots_sem
 * 
 * @return sem_t* 
 */
extern sem_t *global_get_empty_slots_sem();
/*
 * @brief Retorna o semaforo dos assentos
 * 
 * @return sem_t* 
 */
extern sem_t* global_get_semaphore_conveyor();

/**
 * @brief Retorna o mutex usado para entrar no conveyor
 * 
 * @return pthread_mutex_t* 
 */
extern pthread_mutex_t* global_get_mutex_conveyor_enter();

/**
 * @brief Retorna o mutex usado para escolher o seat no conveyor
 * 
 * @return pthread_mutex_t* 
 */
extern pthread_mutex_t* global_get_mutex_conveyor_seat();


/**
 * @brief Retorna o semaforo dos pratos(dishes - sushichef)
 * @return sem_t* 
 */
sem_t* global_get_semaphore_sushi_dishes();

/**
 * @brief Finaliza todas as variáveis globais.
 * 
 */
extern void globals_finalize();

#endif  // __GLOBALS_H__
