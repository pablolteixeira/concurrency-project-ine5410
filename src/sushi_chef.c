#include <stdio.h>
#include <stdlib.h>

#include "sushi_chef.h"
#include "globals.h"
#include "menu.h"


void* sushi_chef_run(void* arg) {
    sushi_chef_t* self = (sushi_chef_t*) arg;
    virtual_clock_t* global_clock = globals_get_virtual_clock();

    /* Ramdomly prepare and add dishes to the conveyor belt */
    while (TRUE) {
        enum menu_item next_dish = rand() % 5;
        prepare_food(self, next_dish);
        place_food_at_the_conveyor(self, next_dish);
    }

    pthread_exit(NULL);
}

void seat_at_conveyor_slot(sushi_chef_t* self, conveyor_belt_t* conveyor) {
    /* INSIRA SUA LÓGICA AQUI */
}

void leave_conveyor_slot(sushi_chef_t* self, conveyor_belt_t* conveyor) {
    /* INSIRA SUA LÓGICA AQUI */
}

void place_food_at_the_conveyor(sushi_chef_t* self, enum menu_item dish) {
    /* INSIRA SUA LÓGICA AQUI */
    conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();
    conveyor_belt->_slots[self->_seat_position] = dish;
}

void prepare_food(sushi_chef_t* self, enum menu_item menu_item) {
    switch (menu_item) {
        case Sushi:
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d started preparing Sushi!\n", self->_id);
            msleep(SUSHI_PREP_TIME/self->_preparation_speed);
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d finished preparing Sushi!\n", self->_id);
            break;
        case Dango:
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d started preparing Dango!\n", self->_id);
            msleep(DANGO_PREP_TIME/self->_preparation_speed);
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d finished preparing Dango!\n", self->_id);
            break;
        case Ramen:
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d started preparing Ramen!\n", self->_id);
            msleep(RAMEN_PREP_TIME/self->_preparation_speed);
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d finished preparing Ramen!\n", self->_id);
            break;
        case Onigiri:
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d started preparing Onigiri!\n", self->_id);
            msleep(ONIGIRI_PREP_TIME/self->_preparation_speed);
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d finished preparing Onigiri!\n", self->_id);
            break;
        case Tofu:
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d started preparing Tofu!\n", self->_id);
            msleep(TOFU_PREP_TIME/self->_preparation_speed);
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Sushi Chef %d finished preparing Tofu!\n", self->_id);
            break; 
        default:
            fprintf(stdout, RED "[ERROR] Invalid menu_item variant passed to `prepare_food()`.\n" NO_COLOR);
            exit(EXIT_FAILURE);
    }
}

sushi_chef_t* sushi_chef_init(int seat_position, int preparation_speed) {
    sushi_chef_t* self = malloc(sizeof(sushi_chef_t));
    if (self == NULL) {
        fprintf(stdout, RED "[ERROR] Bad malloc() at `sushi_chef_t* sushi_chef_init()`.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }

    self->_id = rand() % 1000;
    self->_seat_position = seat_position;
    self->_preparation_speed = preparation_speed;

    pthread_create(&self->thread, NULL, sushi_chef_run, (void *) self);

    return self;
}

void sushi_chef_finalize(sushi_chef_t* self) {
    pthread_join(self->thread, NULL);
    free(self);
}

void print_sushi_chef(sushi_chef_t* self) {
    fprintf(stdout, BLUE "[DEBUG] Sushi Chef " NO_COLOR "{\n");
    fprintf(stdout, BLUE "    _id" NO_COLOR ": %d\n", self->_id);
    fprintf(stdout, BLUE "    _seat_position" NO_COLOR ": %d\n", self->_seat_position);
    fprintf(stdout, NO_COLOR "}\n" NO_COLOR);
}
