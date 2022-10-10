#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "args.h"
#include "messages.h"


config_t parse(int argc, char **argv) {
    int c;
    config_t config = { 50, 2, 10, 5 };

    while ((c = getopt(argc, argv, "n:b:t:s:h")) != -1) {
        switch (c) {
            case 'n':
                config.students = atoi(optarg);
                break;
            case 'b':
                config.buffets = atoi(optarg);
                break;
            case 't':
                config.tables = atoi(optarg);
                break;
            case 's':
                config.seat_per_table = atoi(optarg);
                break;
            case 'h':
                help(argv);
                exit(0);
            default:
                exit(1);
        }
    }

    return config;
}
