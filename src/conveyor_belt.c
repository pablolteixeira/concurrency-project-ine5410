#include <stdio.h>
#include <stdlib.h>

#include "conveyor_belt.h"
#include "virtual_clock.h"
#include "menu.h"


pthread_mutex_t conveyor_mutex;
pthread_cond_t conveyor_rotation_cond_var;

void* conveyor_belt_run(void* arg) {
    conveyor_belt_t* self = (conveyor_belt_t*) arg;
    while (TRUE) {
        msleep(5000);

        /* Lock global conveyor_belt */
        pthread_mutex_lock(&conveyor_mutex);

        fprintf(stdout, GREEN "[INFO]" NO_COLOR " Conveyor belt started moving...\n");
        msleep(2000/self->_belt_speed);

        /* Rotate every conveyor slot by 1 index */
        int last = self->_slots[0];
        for (int i=0; i<self->_max_slots-1; i++) {
            self->_slots[i] = self->_slots[i+1];
        }
        self->_slots[self->_max_slots-1] = last;

        /* Unlock global conveyor belt */
        pthread_cond_broadcast(&conveyor_rotation_cond_var);
        pthread_mutex_unlock(&conveyor_mutex);

        fprintf(stdout, GREEN "[INFO]" NO_COLOR " Conveyor belt finished moving...\n");
        print_conveyor_belt(self);
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
    self->_slots = (int*) malloc(sizeof(int)* self->_max_slots);

    for (int i=0; i<self->_max_slots; i++) {
        /* Initialize conveyor belt slots to -1 */
        if (i==10) {
            self->_slots[i] = 0;
        } else {
            self->_slots[i] = -1;
        }
    }

    pthread_mutex_init(&conveyor_mutex, NULL);
    pthread_cond_init(&conveyor_rotation_cond_var, NULL);

    pthread_create(&self->thread, NULL, conveyor_belt_run, (void *) self);
    print_conveyor_belt(self);

    return self;
}

void conveyor_belt_finalize(conveyor_belt_t* self) {
    pthread_join(self->thread, NULL);
    pthread_mutex_destroy(&conveyor_mutex);
    pthread_cond_destroy(&conveyor_rotation_cond_var);
    free(self);
}

void print_conveyor_belt(conveyor_belt_t* self) {
    fprintf(stdout, BLUE "[DEBUG] Conveyor Belt " NO_COLOR "{\n");
    fprintf(stdout, BLUE "    _empty_slots" NO_COLOR ": %d\n", self->_empty_slots);
    fprintf(stdout, BLUE "    _max_slots" NO_COLOR ": %d\n", self->_max_slots);
    fprintf(stdout, BLUE "    _belt_speed" NO_COLOR ": %d\n", self->_belt_speed);
    fprintf(stdout, BLUE "    _slots" NO_COLOR ": [");
    for (int i=0; i<self->_max_slots; i++) {
        if (i%25 == 0) {
            fprintf(stdout, NO_COLOR "\n        ");
        }
        switch (self->_slots[i]) {
            case -1:
                fprintf(stdout, NO_COLOR "%s, ", EMPTY);
                break;
            case 0:
                fprintf(stdout, NO_COLOR "%s, ", SUSHI);
                break;
            case 1:
                fprintf(stdout, NO_COLOR "%s, ", DANGO);
                break;
            case 2:
                fprintf(stdout, NO_COLOR "%s, ", RAMEN);
                break;
            case 3:
                fprintf(stdout, NO_COLOR "%s, ", ONIGIRI);
                break;
            case 4:
                fprintf(stdout, NO_COLOR "%s, ", TOFU);
                break;
            default:
                fprintf(stdout, RED "[ERROR] Invalid menu item code in the Conveyor Belt.\n" NO_COLOR);
                exit(EXIT_FAILURE);
        }
    }
    fprintf(stdout, NO_COLOR "\n    ]\n");
    fprintf(stdout, NO_COLOR "}\n" NO_COLOR);
}
