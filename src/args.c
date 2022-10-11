#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "args.h"


config_t parse(int argc, char **argv) {
    int c;
    config_t config = { 50, 2, 100, 10, 18, 60 };

    while ((c = getopt(argc, argv, "s:c:b:o:x:m:h")) != -1) {
        switch (c) {
            case 's':
                config.seats = atoi(optarg);
                break;
            case 'c':
                config.sushi_chefs = atoi(optarg);
                break;
            case 'b':
                config.conveyor_belt_capacity = atoi(optarg);
                break;
            case 'o':
                config.opening_time = atoi(optarg);
                break;
            case 'x':
                config.closing_time = atoi(optarg);
                break;
            case 'm':
                config.clock_speed_multiplier = atoi(optarg);
                break;
            case 'h':
                help(argv);
                exit(0);
            default:
                exit(1);
        }
    }
    simulation_summary(&config);
    return config;
}

void help(char** argv) {
    title();
    description();
    usage(argv[0]);
    version();
    bar();
}

void simulation_summary(config_t* config) {
    title();
    configuration(config);
    separator();
}

void title() {
    fprintf(stdout, MAGENTA TITLE NO_COLOR);
}

void bar() {
    fprintf(stdout, MAGENTA BAR NO_COLOR);
}

void separator() {
    fprintf(stdout, MAGENTA SEPARATOR NO_COLOR);
}

void usage(char* program_name) {
    fprintf(stdout, MAGENTA "Usage: " NO_COLOR "%s [OPTIONS]\n", program_name);
    fprintf(stdout, MAGENTA "Options:\n" NO_COLOR);
    fprintf(stdout, "  -t  Number of seats (default=50).\n");
    fprintf(stdout, "  -s  Number of sushi chefs (default=2).\n");
    fprintf(stdout, "  -c  Conveyor belt capacity (default=100).\n");
    fprintf(stdout, "  -o  Opening time (default=10).\n");
    fprintf(stdout, "  -x  Closing time (default=18).\n");
    fprintf(stdout, "  -m  Clock speed multiplier (default=60).\n");
    fprintf(stdout, "  -h  Prints this help.\n");
}

void configuration(config_t* config) {
    fprintf(stdout, MAGENTA "Simulation configuration parameters:\n" NO_COLOR);
    fprintf(stdout, GREEN "  Seats                   " NO_COLOR "%d\n", config->seats);
    fprintf(stdout, GREEN "  Sushi Chefs             " NO_COLOR "%d\n", config->sushi_chefs);
    fprintf(stdout, GREEN "  Conveyor Belt Capacity  " NO_COLOR "%d\n", config->conveyor_belt_capacity);
    fprintf(stdout, GREEN "  Opening time            " NO_COLOR "%dh\n", config->opening_time);
    fprintf(stdout, GREEN "  Closing time            " NO_COLOR "%dh\n", config->closing_time);
    fprintf(stdout, GREEN "  Clock speed multiplier  " NO_COLOR "%dx\n", config->clock_speed_multiplier);
}

void description() {
    fprintf(stdout, MAGENTA "Description: " NO_COLOR);
    fprintf(stdout, "This is the first concurrent programming assignment for ine5410 2022.2!\n");
}

void version() {
    fprintf(stdout, MAGENTA "Version: " GRAY "%s\n" NO_COLOR, __PROGRAM_VERSION__);
}

