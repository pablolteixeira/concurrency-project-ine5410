#ifndef __MENU_H__
#define __MENU_H__


/**
 * @brief Máximo e mínimo de pratos desejados
*/
#define MINIMUM                  0
#define MAXIMUM                  2

/**
 * @brief Pratos do Sushi Shop.
*/
enum menu_item {
    Sushi=0,
    Onigiri=1,
    Tonkatsu=2,
    Gyosa=3,
    Tofu=4,
};

#endif  //__MENU_H__
