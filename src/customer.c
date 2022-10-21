#include <stdio.h>
#include <stdlib.h>

#include "virtual_clock.h"
#include "customer.h"
#include "globals.h"


void* customer_run(void* arg) {
    /* MODIFIQUE ESSA FUNÇÃO PARA GARANTIR O COMPORTAMENTO CORRETO E EFICAZ DO CLIENTE */
    /* NOTAS:
     * 1. A PRIMEIRA AÇÃO REALIZADA SERÁ ESPERAR NA FILA GLOBAL DE CLIENTES, ATÉ QUE O HOSTESS
     *    GUIE O CLIENTE PARA UM ASSENTO LIVRE.
     * 2. APÓS SENTAR-SE, O CLIENTE IRÁ COMEÇAR A PEGAR E COMER OS SUSHIS DA ESTEIRA
     * 3. O CLIENTE SÓ PODE PEGAR UM PRATO QUANDO A ESTEIRA ESTIVER PARADA
     * 4. O CLIENTE SÓ PEGARÁ PRATOS CASO ELE DESEJE-OS, INFORMAÇÃO CONTIDA NO ARRAY self->_wishes[..]
     * 5. APÓS CONSUMIR TODOS OS PRATOS DESEJADOS, O CLIENTE DEVERÁ SAIR DA ESTEIRA
     * 6. QUANTO O RESTAURANTE FECHAR, O CLIENTE DEVERÁ SAIR IMEDIATAMENTE DA ESTEIRA. CASO ELE ESTEJE
     *    NO PROCESSO DE COMER ALGUM ITEM, ELE DEVE TERMINAR DE COMER E SAIR IMEDIATAMENTE EM SEGUIDA.
     * 7. CUIDADO COM ERROS DE CONCORRÊNCIA
    */ 
    customer_t* self = (customer_t*) arg;

    /* INSIRA SUA LÓGICA AQUI */
    msleep(1000000);
    pthread_exit(NULL);
}

void customer_pick_food(int food_slot) {
    /* INSIRA SUA LÓGICA AQUI */
    /* NOTAS:
     * 1. LEMBRE-SE: O CLIENTE SÓ PODE COMEÇAR A PEGAR COMIDA APÓS ESTAR SENTADO EM UMA VAGA
     *    DA ESTEIRA. O VALOR customer_t->_seat_position É ATUALIZADO PELO HOSTESS.
     * 2. O CLIENTE PODE PEGAR COMIDA DE TRÊS POSSÍVEIS SLOTS: i-1, i, i+1, ONDE i É O ÍNDICE 
     *    POSICIONAL DO CLIENTE NA ESTEIRA.
     * 3. CUIDADO COM PROBLEMAS DE SINCRONIZAÇÃO!
    */
}

void customer_eat(customer_t* self, enum menu_item food) {
    /* INSIRA SUA LÓGICA AQUI */
    /* NOTAS:
     * 1. LEMBRE-SE DE DECREMENTAR OS ITENS DA LISTA DE DESEJOS DO CLIENTE CONFORME ELE CONSUMIR AS COMIDAS!
    */


    /* NÃO EDITE O CONTEÚDO ABAIXO */
    virtual_clock_t* global_clock = globals_get_virtual_clock();
    switch (food) {
        case Sushi:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Sushi!\n", self->_id);
            msleep(SUSHI_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Sushi!\n", self->_id);
            break;
        case Dango:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Dango!\n", self->_id);
            msleep(DANGO_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Dango!\n", self->_id);
            break;
        case Ramen:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Ramen!\n", self->_id);
            msleep(RAMEN_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Ramen!\n", self->_id);
            break;
        case Onigiri:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Onigiri!\n", self->_id);
            msleep(ONIGIRI_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Onigiri!\n", self->_id);
            break;
        case Tofu:
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d started eating Tofu!\n", self->_id);
            msleep(TOFU_PREP_TIME/global_clock->clock_speed_multiplier);
            print_virtual_time(globals_get_virtual_clock());
            fprintf(stdout, GREEN "[INFO]" NO_COLOR " Customer %d finished eating Tofu!\n", self->_id);
            break; 
        default:
            fprintf(stdout, RED "[ERROR] Invalid menu_item variant passed to `customer_eat()`.\n" NO_COLOR);
            exit(EXIT_FAILURE);
    }
}

void customer_leave(customer_t* self) {
    /* INSIRA SUA LÓGICA AQUI */
    /* NOTAS:
     * 1. LEMBRE-SE: O CLIENTE DEVERÁ SAIR DA ESTEIRA (ATUALIZAR O VALOR DO SEAT GLOBAL NO CONVEYOR)
     *    SOMENTE APÓS TER CONSUMIDO TODOS OS ITENS DA SUA LISTA DE DESEJOS, OU QUANDO O RESTAURANTE
     *    FECHAR.
    */
    conveyor_belt_t* conveyor_belt = globals_get_conveyor_belt();
}

customer_t* customer_init() {
    customer_t* self = malloc(sizeof(customer_t));
    if (self == NULL) {
        fprintf(stdout, RED "[ERROR] Bad malloc() at `customer_t* customer_init()`.\n" NO_COLOR);
        exit(EXIT_FAILURE);
    }
    self->_id = rand() % 1000;
    for (int i=0; i<=4; i++) {
        self->_wishes[i] = (rand() % 4);
    }
    self->_seat_position = -1;
    pthread_create(&self->thread, NULL, customer_run, (void *) self);
    return self;
}

void customer_finalize(customer_t* self) {
    pthread_join(self->thread, NULL);
    free(self);
}

void print_customer(customer_t* self) {
    print_virtual_time(globals_get_virtual_clock());
    fprintf(stdout, BROWN "[DEBUG] Customer " NO_COLOR "{\n");
    fprintf(stdout, BROWN "    _id" NO_COLOR ": %d\n", self->_id);
    fprintf(stdout, BROWN "    _wishes" NO_COLOR ": [%d, %d, %d, %d, %d]\n", self->_wishes[0], self->_wishes[1], self->_wishes[2], self->_wishes[3], self->_wishes[4]);
    fprintf(stdout, BROWN "    _seat_position" NO_COLOR ": %d\n", self->_seat_position);
    fprintf(stdout, NO_COLOR "}\n" NO_COLOR);
}
