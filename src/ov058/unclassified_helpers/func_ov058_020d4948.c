#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_0000[0x1048];
    u8 targetType;
} Enemy;

extern VecFx32 *func_ov052_020ceb54(Enemy *enemy);

BOOL func_ov058_020d4948(Enemy *enemy, VecFx32 *point)
{
    BOOL outside = TRUE;
    VecFx32 position = *func_ov052_020ceb54(enemy);
    VecFx32 target = *point;

    switch (enemy->targetType) {
    case 2:
    case 3:
        if (target.y >= position.y + 0x1000 && target.y < position.y + 0x2000) {
            outside = FALSE;
        }
        break;
    }
    return outside;
}
