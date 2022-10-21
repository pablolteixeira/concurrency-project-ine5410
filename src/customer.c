#include <stdio.h>
#include <stdlib.h>

#include "virtual_clock.h"
#include "customer.h"
#include "globals.h"


void* customer_run(void* arg) {
    /* MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO CLIENTE */
    /* NOTAS:
     * 1. A PRIMEIRA AÇÃO REALIZADA SERÁ SENTAR-SE EM ALGUMA POSIÇÃO LIVRE DA ESTEIRA
     * 2. APÓS SENTAR-SE, O CLIENTE IRÁ COMEÇAR A PEGAR E COMER OS SUSHIS DA ESTEIRA
     * 3. O CLIENTE SÓ PODE PEGAR UM PRATO QUANDO A ESTEIRA ESTIVER PARADA
     * 4. O CLIENTE SÓ PEGARÁ PRATOS CASO ELE DESEJE-OS, INFORMAÇÃO CONTIDA NO ARRAY self->_wishes[..]
     * 5. APÓS CONSUMIR TODOS OS PRATOS DESEJADOS, O CLIENTE DEVERÁ SAIR DA ESTEIRA
     * 6. CUIDADO COM ERROS DE CONCORRÊNCIA
    */ 
    customer_t* self = (customer_t*) arg;
    conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();

    pthread_exit(NULL);
}

void customer_seat(customer_t* self) {
    /* INSIRA SUA LÓGICA AQUI */
    conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();
}

void customer_pick_food(int food_slot) {
    /* INSIRA SUA LÓGICA AQUI */
}

void customer_eat(customer_t* self, enum menu_item food) {
    /* INSIRA SUA LÓGICA AQUI */
    conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();
}

void customer_leave(customer_t* self) {
    /* INSIRA SUA LÓGICA AQUI */
    conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();
}

customer_t* customer_init() {
    customer_t* self = malloc(sizeof(customer_t));
    if (self == NULL) {
        fprintf(stdout, RED "[ERROR] Bad malloc() at `customer_t* customer_init()`.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }
    self->_id = rand() % 1000;
    self->_is_drinking = rand() % 2;
    for (int i=0; i<=4; i++) {
        self->_wishes[i] = (rand() % 4);
    }
    self->_seat_position = -1;
    pthread_create(&self->thread, NULL, customer_run, (void *) self);
    return self;
}

void customer_finalize(customer_t* self) {
    pthread_join(self->thread, NULL);
    free(self);
}

void print_customer(customer_t* self) {
    print_virtual_time(globals_get_virtual_clock());
    fprintf(stdout, BROWN "[DEBUG] Customer " NO_COLOR "{\n");
    fprintf(stdout, BROWN "    _id" NO_COLOR ": %d\n", self->_id);
    fprintf(stdout, BROWN "    _wishes" NO_COLOR ": [%d, %d, %d, %d, %d]\n", self->_wishes[0], self->_wishes[1], self->_wishes[2], self->_wishes[3], self->_wishes[4]);
    fprintf(stdout, BROWN "    _is_drinking" NO_COLOR ": %d\n", self->_is_drinking);
    fprintf(stdout, BROWN "    _seat_position" NO_COLOR ": %d\n", self->_seat_position);
    fprintf(stdout, NO_COLOR "}\n" NO_COLOR);
}
