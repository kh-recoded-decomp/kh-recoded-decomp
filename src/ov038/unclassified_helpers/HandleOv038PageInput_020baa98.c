#include "nitro/types.h"

typedef struct Ov038Context {
    u8 pad_0000[0xd0ac];
    s32 page;
} Ov038Context;

extern Ov038Context *g_ov038Context_020bd144;
extern u16 data_02060500;
extern void PlaySoundEffect_0204d924(int player, int sound);
extern void ResetOv038ExitState_020bb638(int state);
extern void SetOv038SpriteOffset_020bb2ac(s32 poolIndex, s32 spriteIndex, s32 offsetX, s32 offsetY);

s32 HandleOv038PageInput_020baa98(void)
{
    Ov038Context *ctx = g_ov038Context_020bd144;
    s32 index;

    switch (data_02060500 & 0x301) {
    case 1:
        PlaySoundEffect_0204d924(0, 1);
        ResetOv038ExitState_020bb638(3);
        break;
    case 0x100:
    case 0x200:
        ctx->page = (ctx->page + 1) % 2;
        switch (ctx->page) {
        case 0:
            *(vu32 *)0x04001010 = 0;
            for (index = 0; index < 99; index++) {
                if (index != 0x38) {
                    SetOv038SpriteOffset_020bb2ac(1, index, 0, 0);
                }
            }
            break;
        case 1:
            *(vu32 *)0x04001010 = 0x100;
            for (index = 0; index < 99; index++) {
                if (index != 0x38) {
                    SetOv038SpriteOffset_020bb2ac(1, index, -0x100, 0);
                }
            }
            break;
        }
        PlaySoundEffect_0204d924(0, 2);
        break;
    }
    return 0;
}
