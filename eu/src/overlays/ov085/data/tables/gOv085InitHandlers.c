#include "nitro/types.h"

extern void func_ov085_020bf810(void);
typedef struct ShopMenu ShopMenu;
extern void ResetShopMenuGraphics(ShopMenu *menu);

void (*gOv085InitHandlers[2])(void) = {
    func_ov085_020bf810,
    (void (*)(void))ResetShopMenuGraphics,
};
