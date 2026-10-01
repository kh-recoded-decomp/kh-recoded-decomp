#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 mode;
    u32 flags;
    u8 pad_08[0x0c];
    s32 unk_14;
    u8 pad_18[0x08];
    s32 chaseTimer;
    u8 pad_24[0x0c];
    VecFx32 anchor;
} AiState;

typedef struct {
    u8 pad_00[0x0e];
    u16 buttons;
} InputState;

typedef struct Enemy Enemy;

struct Enemy {
    u8 pad_0000[0x21c];
    u32 (*getStatus)(Enemy *enemy);
    u8 pad_0220[0x1048 - 0x220];
    u8 targetKind;
    u8 pad_1049[0x1258 - 0x1049];
    AiState ai;
};

extern Enemy *g_player_020d8a20;
extern VecFx32 *func_ov052_020ceb54(Enemy *enemy);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

static inline u32 Enemy_GetStatus(Enemy *enemy)
{
    if (enemy->getStatus != NULL) {
        return enemy->getStatus(enemy);
    }
    return 0;
}

void func_ov058_020d4a34(Enemy *enemy, InputState *input)
{
    AiState *ai = &enemy->ai;
    fx32 distance = func_01ffa0f4(func_ov052_020ceb54(g_player_020d8a20), func_ov052_020ceb54(enemy));
    fx32 margin = 0;
    BOOL locked = FALSE;
    u32 flags;

    if (enemy->ai.mode == 3) {
        ai->mode = 1;
    }
    flags = ai->flags;
    if (flags & 0x80000) {
        return;
    }
    if (g_player_020d8a20->targetKind == 1) {
        margin = 0x2000;
        locked = TRUE;
    }
    if (margin + 0x4000 < distance) {
        if (locked && !(flags & 0x80)) {
            ai->chaseTimer = 0x1e000;
            ai->flags |= 0x80;
        }
        if (ai->chaseTimer <= 0) {
            ai->mode = 3;
        }
        return;
    }
    if ((distance > 0x3000 && (input->buttons & 0x40)) || (Enemy_GetStatus(enemy) & 8)) {
        ai->mode = 3;
    } else {
        input->buttons = 0;
        ai->unk_14 = 0;
        ai->flags &= ~0x80;
        ai->anchor = *func_ov052_020ceb54(enemy);
    }
}
