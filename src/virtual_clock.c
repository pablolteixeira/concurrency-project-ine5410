#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "virtual_clock.h"


void* clock_run(void* data) {
    virtual_clock_t* self = (virtual_clock_t*) data;
    while (TRUE) {
        read_clock(self);
        if (self->current_time >= DAY) {
            /* The virtual clock stops after 1 day has passed since time 0 */
            break;
        }
        /* A cada segundo, o relógio virtual é incrementado por (1 x multiplier) segundos */
        self->current_time += 1;
        msleep(1000/self->clock_speed_multiplier);
    }
    pthread_exit(NULL);
}

virtual_clock_t* clock_init(config_t* config) {
    virtual_clock_t* self = malloc(sizeof(virtual_clock_t));
    if (self == NULL) {
        fprintf(stdout, RED "[ERROR] Bad malloc() at `virtual_clock_t* clock_init()`.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }
    self->clock_speed_multiplier = config->clock_speed_multiplier;
    self->opening_time = 3600 * config->opening_time;
    self->closing_time = 3600 * config->closing_time;
    self->current_time = 3600 * config->opening_time;
    pthread_create(&self->thread, NULL, clock_run, (void *) self);
    return self;
}

void clock_finalize(virtual_clock_t* self) {
    pthread_join(self->thread, NULL);
    free(self);
}

unsigned int read_hours(unsigned int value) {
    return value / HOUR;
}

unsigned int read_minutes(unsigned int value) {
    return (value / MINUTE) % MINUTE;
}

unsigned int read_seconds(unsigned int value) {
    return value % MINUTE;
}

void read_clock(virtual_clock_t* self) {
    fprintf(stdout, GRAY "%02dh%02dm%02ds\n" NO_COLOR, read_hours(self->current_time), read_minutes(self->current_time), read_seconds(self->current_time));
}

int msleep(long msec) {
    struct timespec ts;
    int res;

    if (msec < 0) {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}
