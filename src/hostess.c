#include <stdlib.h>

#include "hostess.h"
#include "globals.h"
#include "args.h"


int hostess_check_for_a_free_conveyor_seat() {
    /* MODIFIQUE ESSA FUNÇÃO ADICIONANDO A LÓGICA NECESSÁRIA */
    /* NOTES:
     * 1. O Hostess deve ficar em espera até que uma vaga seja liberada na esteira
     * 2. A vaga inicial (conveyor->_seats[0]) é reservada para o Sushi Chef
     * 3. Não remova os prints, nem o msleep de dentro do while loop
     * 4. O retorno dessa função é o índice do conveyor indicando um assento livre
     * 5. Cuidado com problemas de sincronização!
    */
    conveyor_belt_t* conveyor = globals_get_conveyor_belt();
    virtual_clock_t* virtual_clock = globals_get_virtual_clock();
    
    print_virtual_time(globals_get_virtual_clock());
    fprintf(stdout, GREEN "[INFO]" NO_COLOR " O Hostess está procurando por um assento livre...\n");
    print_conveyor_belt(conveyor);

    while (TRUE) {
        for (int i=0; i<conveyor->_size; i++) {
            if (conveyor->_seats[i] == -1 && i !=0) {  // Atenção à regra! (-1 = livre, 0 = sushi_chef, 1 = customer)
                print_virtual_time(globals_get_virtual_clock());
                fprintf(stdout, GREEN "[INFO]" NO_COLOR " O Hostess encontrou o assento %d livre para o próximo cliente!\n", i);
                return i;
            }
        }
        msleep(120000/virtual_clock->clock_speed_multiplier);  // Não remova esse sleep!
    }
}

void hostess_guide_first_in_line_customer_to_conveyor_seat(int seat) {
    /* MODIFIQUE ESSA FUNÇÃO ADICIONANDO A LÓGICA NECESSÁRIA */
    /* NOTES:
     * 1. Nessa função é papel do Hostess garantir 3 atualizações:
     *    a. O valor _seat_position do cliente em questão deve ser atualizado
     *    b. O valor do assento em questão no conveyor_belt global deve ser atualizado (-1 = vazio, 0 = sushi_chef, 1 = cliente)
     *    c. O cliente em questão deve ser removido da fila global
     * 2. Cuidado com problemas de sincronização!
     * 3. Não remova os prints!
    */
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
    /* MODIFIQUE ESSA FUNÇÃO ADICIONANDO A LÓGICA NECESSÁRIA */
    /* NOTAS:
     * 1. O Hostess deve funcionar em loop, retirando clientes da fila global e adicionando-os na
     *    esteira conforme vagas são encontradas. Use as funções `hostess_check_for_a_free_conveyor_seat` e
     *    `hostess_guide_first_in_line_customer_to_conveyor_seat` para realizar as ações necessárias
     * 2. Quando o sushi shop fechar, o Hostess deve parar de guiar novos clientes para a esteira, e 
     *    esvaziar a fila global, finalizando os clientes em espera, e por fim finalizando-se por meio
     *    da chamada pthread_exit(NULL)
     * 3. Atenção para os problemas de concorrência!
     * 4. Não remova os prints!
    */
    virtual_clock_t* virtual_clock = globals_get_virtual_clock();
    queue_t* queue = globals_get_queue();
    int sushi_shop_fechado = FALSE;

    while (sushi_shop_fechado == FALSE) {  // Adicione a lógica para que o Hostess realize o fechamento do Sushi Shop!
        if (queue->_length > 0) {
            int seat = hostess_check_for_a_free_conveyor_seat();
            hostess_guide_first_in_line_customer_to_conveyor_seat(seat);
        }
        msleep(3000/virtual_clock->clock_speed_multiplier);  // Não remova esse sleep!
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
