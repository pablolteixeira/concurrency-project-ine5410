#include <stdio.h>
#include <stdlib.h>

#include "conveyor_belt.h"
#include "virtual_clock.h"


pthread_mutex_t conveyor_mutex;
pthread_cond_t conveyor_cond_var;

void* conveyor_belt_run(void* arg) {
    conveyor_belt_t* self = (conveyor_belt_t*) arg;
    while (TRUE) {
        /* The sushi conveyor belt will rotate periodically */
        msleep(10000);

        /* Lock global conveyor_belt */
        pthread_mutex_lock(&conveyor_mutex); 

        /* Rotate every conveyor slot by 1 index */
        fprintf(stdout, GREEN "[INFO]" NO_COLOR " Conveyor belt started moving...\n");
        msleep(2000/self->_belt_speed);

        /* Unlock global conveyor belt */
        pthread_cond_broadcast(&conveyor_cond_var);
        pthread_mutex_unlock(&conveyor_mutex);

        fprintf(stdout, GREEN "[INFO]" NO_COLOR " Conveyor belt finished moving...\n");
    }
    pthread_exit(NULL);
}

conveyor_belt_t* conveyor_belt_init(config_t* config) {
    conveyor_belt_t* self = malloc(sizeof(conveyor_belt_t));
    if (self == NULL) {
        fprintf(stdout, RED "[ERROR] Bad malloc() at `conveyor_belt_t* conveyor_belt_init()`.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }

    self->_empty_slots = config->conveyor_belt_capacity;
    self->_max_slots = config->conveyor_belt_capacity;
    self->_belt_speed = config->conveyor_belt_speed;

    pthread_mutex_init(&conveyor_mutex, NULL);
    pthread_cond_init(&conveyor_cond_var, NULL);

    pthread_create(&self->thread, NULL, conveyor_belt_run, (void *) self);

    return self;
}

void conveyor_belt_finalize(conveyor_belt_t* self) {
    pthread_join(self->thread, NULL);
    pthread_mutex_destroy(&conveyor_mutex);
    pthread_cond_destroy(&conveyor_cond_var);
    free(self);
}

void print_conveyor_belt(conveyor_belt_t* self) {
    fprintf(stdout, BLUE "[DEBUG] Conveyor Belt " NO_COLOR "{\n");
    fprintf(stdout, BLUE "    _empty_slots" NO_COLOR ": %d\n", self->_empty_slots);
    fprintf(stdout, BLUE "    _max_slots" NO_COLOR ": %d\n", self->_max_slots);
    fprintf(stdout, BLUE "    _belt_speed" NO_COLOR ": %d\n", self->_belt_speed);
    fprintf(stdout, NO_COLOR "  }\n" NO_COLOR);
}
