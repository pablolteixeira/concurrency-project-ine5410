#include <stdlib.h>

#include "hostess.h"
#include "globals.h"
#include "args.h"


int hostess_check_for_a_free_conveyor_seat() {
    /* 
        MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO HOSTESS.
        NOTAS:
        1.  O HOSTESS DEVE FICAR EM ESPERA ATÉ QUE UMA VAGA SEJA LIBERADA NA ESTEIRA.
        2.  A VAGA INICIAL (conveyor->_seats[0]) É RESERVADA PARA O SUSHI CHEF.
        3.  NÃO REMOVA OS PRINTS, NEM O `msleep()` DE DENTRO DO WHILE LOOP.
        4.  O RETORNO DESSA FUNÇÃO É O ÍNDICE DO CONVEYOR INDICANDO UM ASSENTO LIVRE.
        5.  CUIDADO COM PROBLEMAS DE SINCRONIZAÇÃO!
    */
    conveyor_belt_t* conveyor = globals_get_conveyor_belt();
    virtual_clock_t* virtual_clock = globals_get_virtual_clock();
    sem_t* semaphore = global_get_semaphore_conveyor();
    pthread_mutex_t* mutex_conveyor_enter = global_get_mutex_conveyor_enter();


    print_virtual_time(globals_get_virtual_clock());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " O Hostess está procurando por um assento livre...\n");
    print_conveyor_belt(conveyor);


    sem_wait(semaphore);

    while (TRUE) {
        pthread_mutex_lock(mutex_conveyor_enter);
        for (int i=0; i<conveyor->_size; i++) {
            if (conveyor->_seats[i] == -1 && i !=0) {  // Atenção à regra! (-1 = livre, 0 = sushi_chef, 1 = customer)
                print_virtual_time(globals_get_virtual_clock());
                fprintf(stdout, GREEN "[INFO]" NO_COLOR " O Hostess encontrou o assento %d livre para o próximo cliente!\n", i);
                pthread_mutex_unlock(mutex_conveyor_enter);
                return i;
            }
        }

        msleep(120000/virtual_clock->clock_speed_multiplier);  // Não remova esse sleep!
    }
}

void hostess_guide_first_in_line_customer_to_conveyor_seat(int seat) {
    /* 
        MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO HOSTESS.
        NOTAS:
        1.  NESSA FUNÇÃO É PAPEL DO HOSTESS GARANTIR 3 ATUALIZAÇÕES:
            a. O valor _seat_position do cliente em questão deve ser atualizado
            b. O valor do assento em questão no conveyor_belt global deve ser atualizado 
               (-1 = vazio, 0 = sushi_chef, 1 = cliente)
            c. O cliente em questão deve ser removido da fila global
        2.  CUIDADO COM PROBLEMAS DE SINCRONIZAÇÃO!
        3.  NÃO REMOVA OS PRINTS!
    */

    conveyor_belt_t* conveyor = globals_get_conveyor_belt();
    queue_t* queue = globals_get_queue();
    sem_t* semaphore = global_get_semaphore_conveyor();
    pthread_mutex_t* mutex_conveyor_seat = global_get_mutex_conveyor_seat();

    pthread_mutex_lock(mutex_conveyor_seat);
    customer_t* customer = queue_remove(queue);
    conveyor->_seats[seat] = 1;
    customer->_seat_position=seat;
    pthread_mutex_unlock(mutex_conveyor_seat);

    sem_post(semaphore);
    print_virtual_time(globals_get_virtual_clock());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " O Hostess levou o cliente %d para o assento %d!\n", customer->_id, seat);
    print_conveyor_belt(conveyor);    
}

void* hostess_run() {
    /* 
        MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO HOSTESS.
        NOTAS:
        1.  O HOSTESS DEVE FUNCIONAR EM LOOP, RETIRANDO CLIENTES DA FILA GLOBAL E ADICIONANDO-OS NA
            ESTEIRA GLOBAL CONFORME VAGAS SÃO LIBERADAS.
        2.  QUANDO O SUSHI SHOP FECHAR, O HOSTESS DEVE PARAR DE GUIAR NOVOS CLIENTES DA FILA PARA 
            A ESTEIRA, E ESVAZIAR A FILA GLOBAL, FINALIZANDO OS CLIENTES EM ESPERA.
        3.  CUIDADO COM PROBLEMAS DE SINCRONIZAÇÃO!
        4.  NÃO REMOVA OS PRINTS!
    */
    virtual_clock_t* virtual_clock = globals_get_virtual_clock();
    queue_t* queue = globals_get_queue();
    sem_t* semaphore = global_get_semaphore_conveyor();

    pthread_mutex_t* mutex_conveyor_enter = global_get_mutex_conveyor_enter();
    pthread_mutex_t* mutex_conveyor_seat = global_get_mutex_conveyor_seat();
    conveyor_belt_t* conveyor = globals_get_conveyor_belt();

    int sushi_shop_fechado = FALSE;
    
    sem_init(semaphore, 0, (conveyor->_size - 1));

    pthread_mutex_init(mutex_conveyor_seat, NULL);
    pthread_mutex_init(mutex_conveyor_enter, NULL);
    
    while (sushi_shop_fechado == FALSE) {  // Adicione a lógica para que o Hostess realize o fechamento do Sushi Shop!
        if (queue->_length > 0) {
            int seat = hostess_check_for_a_free_conveyor_seat();
            printf("Esse é o seat %d\n", seat);
            hostess_guide_first_in_line_customer_to_conveyor_seat(seat);
        }
        msleep(3000/virtual_clock->clock_speed_multiplier);  // Não remova esse sleep!
    }

    if (sushi_shop_fechado) {
        queue_finalize(queue);
    }

    pthread_mutex_destroy(mutex_conveyor_seat);
    pthread_mutex_destroy(mutex_conveyor_enter);

    sem_destroy(semaphore);

    pthread_exit(NULL);
}

hostess_t* hostess_init() {
    /* NÃO PRECISA ALTERAR ESSA FUNÇÃO */
    hostess_t* self = malloc(sizeof(hostess_t));
    if (self == NULL) {
        fprintf(stdout, RED "[ERROR] Bad malloc() at `hostess_t* hostess_init()`.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }
    pthread_create(&self->thread, NULL, hostess_run, NULL);
    return self;
}

void hostess_finalize(hostess_t* self) {
    /* NÃO PRECISA ALTERAR ESSA FUNÇÃO */
    pthread_join(self->thread, NULL);
    free(self);
}
