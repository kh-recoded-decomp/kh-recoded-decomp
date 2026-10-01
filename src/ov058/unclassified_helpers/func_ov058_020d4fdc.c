#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 mode;
    u32 flags;
} AiState;

typedef struct {
    u8 pad_0000[0x1258];
    AiState ai;
} Enemy;

extern BOOL func_ov058_020d46d8(Enemy *enemy, VecFx32 *direction);

BOOL func_ov058_020d4fdc(Enemy *enemy)
{
    VecFx32 direction;
    AiState *ai = &enemy->ai;
    BOOL found;

    if (enemy->ai.mode == 4) {
        ai->mode = 1;
    }
    found = func_ov058_020d46d8(enemy, &direction);
    if (found) {
        ai->mode = 4;
    }
    return found;
}
