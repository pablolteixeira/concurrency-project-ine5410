#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "args.h"
#include "customer.h"
#include "sushi_chef.h"
#include "globals.h"


int main (int argc, char** argv) {
    /* Read command line options */
    config_t config = parse(argc, argv);

    /* Setup random seed */
    srand(time(0));

    /* Setup simulation virtual clock */
    globals_set_virtual_clock(virtual_clock_init(&config));

    /* Setup sushi conveyor belt */
    globals_set_conveyor_belt(conveyor_belt_init(&config));

    customer_t* customer_1 = customer_init(0);

    sushi_chef_t* chef = sushi_chef_init(9, 1);

    /* Join threads and free used memory */
    customer_finalize(customer_1);
    globals_finalize();

    return EXIT_SUCCESS;
}
