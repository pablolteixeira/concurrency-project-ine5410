#include <stdlib.h>

#include "hostess.h"
#include "globals.h"
#include "args.h"


int hostess_check_for_a_free_conveyor_seat() {
    /* MODIFIQUE ESSA FUNÇÃO ADICIONANDO A LÓGICA NECESSÁRIA E EVITANDO BUGS DE CONCORRÊNCIA */
    conveyor_belt_t* conveyor = globals_get_conveyor_belt();
    virtual_clock_t* virtual_clock = globals_get_virtual_clock();
    
    print_virtual_time(globals_get_virtual_clock());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " O Hostess está procurando por um assento livre...\n");
    print_conveyor_belt(conveyor);

    while (TRUE) {
        for (int i=0; i<conveyor->_size; i++) {
            if (conveyor->_seats[i] == -1 && i !=0) {
                print_virtual_time(globals_get_virtual_clock());
                fprintf(stdout, GREEN "[INFO]" NO_COLOR " O Hostess encontrou o assento %d livre para o próximo cliente!\n", i);
                return i;
            }
        }
        msleep(120000/virtual_clock->clock_speed_multiplier);
    }
}

void hostess_guide_first_in_line_customer_to_conveyor_seat(int seat) {
    /* MODIFIQUE ESSA FUNÇÃO ADICIONANDO A LÓGICA NECESSÁRIA E EVITANDO BUGS DE CONCORRÊNCIA */
    conveyor_belt_t* conveyor = globals_get_conveyor_belt();
    queue_t* queue = globals_get_queue();

    customer_t* customer = queue_remove(queue);
    conveyor->_seats[seat] = 1;
    customer->_seat_position=seat;

    print_virtual_time(globals_get_virtual_clock());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " O Hostess levou o cliente %d para o assento %d!\n", customer->_id, seat);
    print_conveyor_belt(conveyor);    
}

void* hostess_run() {
    /* MODIFIQUE ESSA FUNÇÃO ADICIONANDO A LÓGICA NECESSÁRIA E EVITANDO BUGS DE CONCORRÊNCIA */
    /* NOTAS:
     * 1. Atente-se à ordem das operações
     * 2. Não remova os prints
     * 3. Não remova a chamada pthread_exit(NULL)
     * 4. Quando o sushi shop estiver fechado, o hostess deve parar de guiar novos clientes para
     *    o sushi shop, esvaziar a fila e finalizar sua thread
    */
    virtual_clock_t* virtual_clock = globals_get_virtual_clock();
    queue_t* queue = globals_get_queue();
    int sushi_shop_fechado = FALSE;

    while (sushi_shop_fechado == FALSE) {
        if (queue->_length > 0) {
            int seat = hostess_check_for_a_free_conveyor_seat();
            hostess_guide_first_in_line_customer_to_conveyor_seat(seat);
        }
        msleep(3000/virtual_clock->clock_speed_multiplier);
    }

    pthread_exit(NULL);
}

hostess_t* hostess_init() {
    hostess_t* self = malloc(sizeof(hostess_t));
    if (self == NULL) {
        fprintf(stdout, RED "[ERROR] Bad malloc() at `hostess_t* hostess_init()`.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }
    pthread_create(&self->thread, NULL, hostess_run, NULL);
    return self;
}

void hostess_finalize(hostess_t* self) {
    pthread_join(self->thread, NULL);
    free(self);
}
