#include <stdlib.h>

#include "globals.h"

#include <semaphore.h>


/*
    VOCÊ DEVE CRIAR VARIÁVEIS GLOBAIS PARA ARMAZENAR DADOS SOBRE A SIMULAÇÃO.
    NOTAS:
    1.  OS SEGUINTES DADOS DEVEM SER ARMAZENADOS E PRINTADOS AO FIM DA SIMULAÇÃO:
        a. Quantidade de clientes que sentaram-se no conveyor e consumiram todos os itens desejados
        b. Quantidades produzidas de cada alimento
        c. Quantidades consumidas de cada alimento
    2.  SIGA OS EXEMPLOS DE VARIÁVEIS GLOBAIS JÁ EXISTENTES NESSE ARQUIVO PARA CRIAR AS NOVAS.
*/

sem_t global_semaphore_conveyor;
pthread_mutex_t global_mutex_conveyor_enter;
pthread_mutex_t global_mutex_conveyor_seat;

sem_t global_semaphore_sushi_dishes;

pthread_mutex_t global_mutex_custumer_eat;
pthread_mutex_t global_mutex_custumer_pick_food;

virtual_clock_t* global_virtual_clock = NULL;
conveyor_belt_t* global_conveyor_belt = NULL;
queue_t* global_queue = NULL;
sem_t empty_slots_sem;

void globals_set_virtual_clock(virtual_clock_t* virtual_clock) {
    global_virtual_clock = virtual_clock;
}

virtual_clock_t* globals_get_virtual_clock() {
    return global_virtual_clock;
}

void globals_set_conveyor_belt(conveyor_belt_t* conveyor_belt) {
    global_conveyor_belt = conveyor_belt;
}

conveyor_belt_t* globals_get_conveyor_belt() {
    return global_conveyor_belt;
}

void globals_set_queue(queue_t* queue) {
    global_queue = queue;
}

queue_t* globals_get_queue() {
    return global_queue;
}


sem_t* global_get_empty_slots_sem() {
    return &empty_slots_sem;
}

sem_t* global_get_semaphore_conveyor() {
    return &global_semaphore_conveyor;
}

pthread_mutex_t* global_get_mutex_conveyor_enter() {
    return &global_mutex_conveyor_enter;
}

pthread_mutex_t* global_get_mutex_conveyor_seat() {
    return &global_mutex_conveyor_seat;
}

sem_t* global_get_semaphore_sushi_dishes() {
    return &global_semaphore_sushi_dishes;
}

pthread_mutex_t* global_get_mutex_custumer_eat() {
    return &global_mutex_custumer_eat;
}

pthread_mutex_t* global_get_mutex_custumer_pick_food() {
    return &global_mutex_custumer_pick_food;
}

/**
 * @brief Finaliza todas as variáveis globais.
 * Se criar alguma variável global que faça uso de mallocs, lembre-se sempre 
 * de usar o free dentro dessa função.
 */
void globals_finalize() {
    virtual_clock_finalize(global_virtual_clock);
    conveyor_belt_finalize(global_conveyor_belt);
}
