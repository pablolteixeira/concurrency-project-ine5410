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
    Dango=1,
    Ramen=2,
    Onigiri=3,
    Tofu=4,
};

#define SUSHI                    "🍣"
#define DANGO                    "🍡"
#define RAMEN                    "🍜"
#define ONIGIRI                  "🍙"
#define TOFU                     "🧈"

#define EMPTY                    "__"

#define SUSHI_PREP_TIME          10000
#define DANGO_PREP_TIME          10000
#define RAMEN_PREP_TIME          10000
#define ONIGIRI_PREP_TIME        10000
#define TOFU_PREP_TIME           10000

#endif  //__MENU_H__
