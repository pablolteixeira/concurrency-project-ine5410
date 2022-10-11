#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "args.h"
#include "virtual_clock.h"


virtual_clock_t* chefs_clock = NULL;

void malloc_virtual_clock() {
    chefs_clock = malloc(sizeof(virtual_clock_t));
    if (chefs_clock == NULL) {
        fprintf(stdout, RED "Bad Malloc Error.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }
}


int main (int argc, char** argv) {
    /* Read command line options */
    config_t config = parse(argc, argv);

    /* Setup simulation virtual clock */
    malloc_virtual_clock();
    clock_init(chefs_clock, &config);


    /* Join threads and free used memory */
    clock_finalize(chefs_clock);

    return EXIT_SUCCESS;
}
