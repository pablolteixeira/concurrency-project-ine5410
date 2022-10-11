#include <stdio.h>
#include <stdlib.h>

#include "customer.h"
#include "menu.h"
#include "virtual_clock.h"


void* customer_run(void* arg) {
    customer_t* self = (customer_t*) arg;
    //conveyor_belt_t* conveyor_belt = globals_get_conveyor();
    //orders_queue* orders_queue = globals_get_orders_queue();
    
    //customer_seat(self);
    //customer_eat_sushi(self);
    //customer_drink_sake(self);
    //customer_leave(self);

    pthread_exit(NULL);
}

void customer_seat(customer_t* self) {
    /* INSIRA SUA LÓGICA AQUI */
}

void customer_eat_sushi(customer_t* self) {
    /* INSIRA SUA LÓGICA AQUI */
}

void customer_drink_sake(customer_t* self) {
    /* INSIRA SUA LÓGICA AQUI */
}

void customer_leave(customer_t* self) {
    /* INSIRA SUA LÓGICA AQUI */
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
        /* Generate a desired random amount for each menu item */
        self->_wishes[i] = (rand() % (MAXIMUM - MINIMUM + 1));
    }
    self->_seat_position = NOT_SEATED;

    pthread_create(&self->thread, NULL, customer_run, (void *) self);

    return self;
}

void customer_finalize(customer_t* self) {
    pthread_join(self->thread, NULL);
    free(self);
}

void print_customer(customer_t* self) {
    fprintf(stdout, BLUE "  Customer " NO_COLOR "{\n");
    fprintf(stdout, BLUE "    _id" NO_COLOR ": %d\n", self->_id);
    fprintf(stdout, BLUE "    _wishes" NO_COLOR ": [%d, %d, %d, %d, %d]\n", self->_wishes[0], self->_wishes[1], self->_wishes[2], self->_wishes[3], self->_wishes[4]);
    fprintf(stdout, BLUE "    _is_drinking" NO_COLOR ": %d\n", self->_is_drinking);
    fprintf(stdout, BLUE "    _seat_position" NO_COLOR ": %d\n", self->_seat_position);
    fprintf(stdout, NO_COLOR "  }\n" NO_COLOR);
}
