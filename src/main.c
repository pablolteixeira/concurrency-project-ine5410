#include <stdio.h>
#include <stdlib.h>

#include "args.h"
#include "virtual_clock.h"
#include "messages.h"


virtual_clock_t* shop_clock = NULL;

void _configure_coffee_shop() {
    shop_clock = malloc(sizeof(virtual_clock_t));
}


int main (int argc, char** argv) {
    /* Read command line options */
    config_t config = parse(argc, argv);

    #ifdef DEBUG
        fprintf(stdout, BLUE "Simulation config:\n" NO_COLOR);
        fprintf(stdout, BROWN "students: %d\n" NO_COLOR, config.students);
        fprintf(stdout, BROWN "buffets: %d\n" NO_COLOR, config.buffets);
        fprintf(stdout, BROWN "tables: %d\n" NO_COLOR, config.tables);
        fprintf(stdout, BROWN "seat_per_table: %d\n" NO_COLOR, config.seat_per_table);
    #endif

    _configure_coffee_shop();

    clock_init(shop_clock);
    clock_finalize(shop_clock);

    return EXIT_SUCCESS;
}
