#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include <pthread.h>
#include "args.h"


/**
 * @brief Definição de constantes booleanas.
*/
#define FALSE                    0
#define TRUE                     1

/**
 * @brief Definição de constantes úteis para os clientes do Sushi shop.
*/
#define NOT_SEATED               -1

/**
 * @brief Cliente do Sushi Shop.
*/
typedef struct customer {
    int _id;
    int _wishes[5];
    int _is_drinking;
    int _seat_position;
    pthread_t thread;
} customer_t;

customer_t* customer_init();
void* customer_run(void* arg);
void customer_finalize(customer_t* self);

void print_customer(customer_t* self);

#endif  //__CUSTOMER_H__
