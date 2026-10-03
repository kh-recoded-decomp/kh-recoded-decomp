#include "nitro/types.h"

typedef struct ScreenSprite {
    s32 x;
    s32 y;
    s32 active;
    s32 animIndex;
    s32 palette;
    s32 spriteIndex;
} ScreenSprite;

typedef struct ItemScreen {
    u8 pad_00000[0x11ed4];
    ScreenSprite sprites[12];
} ItemScreen;

extern void *func_ov039_020bc1bc(void);
extern void func_0204f0c0(void *records, int index);
extern int PXI_Init_0204f0b4(void *records, int animIndex, int flags);
extern void func_0204f2c0(void *records, int index);
extern void func_0204f178(void *records, int index, int value);
extern void func_0204f2e4(void *records, int index);
extern void Slot_SetMode2Bit_0204f480(void *records, int index, int mode);
extern void func_0204f378(void *records, int index, int value);
extern void func_0204f204(void *records, int index, u16 palette);
extern void func_ov077_020c54e4(ScreenSprite *sprite, void *records, int param);

void SyncScreenSpriteSlots_020c5510(ItemScreen *screen, int param)
{
    void *records = func_ov039_020bc1bc();
    ScreenSprite *sprite;
    int i;

    for (i = 0; i < 12; i++) {
        sprite = &screen->sprites[i];
        if (sprite->spriteIndex >= 0 && sprite->active == 0) {
            func_0204f0c0(records, sprite->spriteIndex);
            sprite->spriteIndex = -1;
        }
    }
    for (i = 0; i < 12; i++) {
        sprite = &screen->sprites[i];
        if (sprite->active != 0) {
            if (sprite->spriteIndex < 0) {
                sprite->spriteIndex = PXI_Init_0204f0b4(records, sprite->animIndex, 0);
                switch (i) {
                case 7:
                    func_0204f2c0(records, sprite->spriteIndex);
                    func_0204f178(records, sprite->spriteIndex, 0);
                    Slot_SetMode2Bit_0204f480(records, sprite->spriteIndex, 0);
                    break;
                case 8:
                case 9:
                case 10:
                case 11:
                    func_0204f178(records, sprite->spriteIndex, 1);
                    Slot_SetMode2Bit_0204f480(records, sprite->spriteIndex, 1);
                    break;
                default:
                    func_0204f2e4(records, sprite->spriteIndex);
                    Slot_SetMode2Bit_0204f480(records, sprite->spriteIndex, 2);
                    break;
                }
                func_0204f378(records, sprite->spriteIndex, 1);
            }
            if (i <= 6 && sprite->palette >= 0) {
                func_0204f204(records, sprite->spriteIndex, sprite->palette);
            }
            func_ov077_020c54e4(sprite, records, param);
        }
    }
}
