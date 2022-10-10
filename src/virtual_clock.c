#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "messages.h"
#include "virtual_clock.h"


unsigned int clock_value = 0;

void* clock_run() {
    while (TRUE) {
        read_clock();
        if (clock_value == STOP_TIME) {
            fprintf(stdout, RED "Simulation ended. Time: %d = %d\n" NO_COLOR, clock_value, STOP_TIME);
            break;
        }
        /* A cada segundo, o relógio virtual é incrementado por (1 x multiplier) segundos */
        clock_value += 1 * CLOCK_SPEED_MULTIPLIER;
        msleep(1000);
    }
    pthread_exit(NULL);
}

void clock_init(virtual_clock_t* self) {
    pthread_create(&self->thread, NULL, clock_run, (void *) NULL);
}

void clock_finalize(virtual_clock_t* self) {
    pthread_join(self->thread, NULL);
    free(self);
}

int read_hours(unsigned int clock_value) {
    return clock_value / 3600;
}

int read_minutes(unsigned int clock_value) {
    return (clock_value / 60) % 60;
}

void read_clock() {
    fprintf(stdout, RED "%02dh%02dm\n" NO_COLOR, read_hours(clock_value), read_minutes(clock_value));
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
