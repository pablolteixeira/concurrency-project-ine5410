#include <stdio.h>
#include <stdlib.h>

#include "messages.h"


void help(char** argv) {
    title();
    description();
    usage(argv[0]);
    version();
    bar();
}

void title() {
    fprintf(stdout, MAGENTA TITLE);
}

void bar() {
    fprintf(stdout, MAGENTA BAR);
}

void usage(char* program_name) {
    fprintf(stdout, MAGENTA "Usage: " NO_COLOR "%s [OPTIONS]\n", program_name);
    fprintf(stdout, MAGENTA "Options:\n" NO_COLOR);
    fprintf(stdout, "  -n  Number of students.\n");
    fprintf(stdout, "  -b  Number of buffets.\n");
    fprintf(stdout, "  -t  Number of tables.\n");
    fprintf(stdout, "  -s  Number of seats per table.\n");
    fprintf(stdout, "  -h  Prints this help.\n");
}

void description() {
    fprintf(stdout, MAGENTA "Description: " NO_COLOR);
    fprintf(stdout, "This is the first concurrent programming assignment for ine5410 2022.2!\n");
}

void version() {
    fprintf(stdout, MAGENTA "Version: " GRAY "%s\n" NO_COLOR, __PROGRAM_VERSION__);
}
