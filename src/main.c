#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "args.h"
#include "virtual_clock.h"


int main (int argc, char** argv) {
    /* Read command line options */
    config_t config = parse(argc, argv);

    /* Setup simulation virtual clock */
    virtual_clock_t* chefs_clock = clock_init(&config);

    /* Join threads and free used memory */
    clock_finalize(chefs_clock);

    return EXIT_SUCCESS;
}
