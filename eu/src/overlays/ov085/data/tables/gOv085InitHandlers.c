#include "nitro/types.h"

extern void InitShopMenu(void);
typedef struct ShopMenu ShopMenu;
extern void ResetShopMenuGraphics(ShopMenu *menu);

void (*gOv085InitHandlers[2])(void) = {
    InitShopMenu,
    (void (*)(void))ResetShopMenuGraphics,
};
