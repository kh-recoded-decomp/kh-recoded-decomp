#include "nitro/types.h"

typedef struct ScreenSprite {
    s32 x;
    s32 y;
    s32 unk_08;
    s32 animIndex;
    s32 unk_10;
    s32 spriteIndex;
} ScreenSprite;

typedef struct ItemScreen {
    u8 pad_00000[0x14];
    u8 work[0x11ebc];
    s32 mode;
    ScreenSprite sprites[12];
    s32 state;
} ItemScreen;

extern s8 data_ov077_020ca0fc[];
extern int func_02029f48(void);
extern void *func_ov039_020bc1bc(void);
extern void func_ov077_020c4bb0(ItemScreen *screen);
extern BOOL func_ov077_020c8bd4(void *work, void *owner, BOOL (*predicate)(void *owner),
                                void (*onClose)(ItemScreen *screen), const s8 *message, int arg);
extern void func_ov077_020c58e0(ItemScreen *screen);
extern void func_ov077_020c4be0(ItemScreen *screen);
extern void SetFlagGatedElementsVisible_020c9d7c(void *container, BOOL visible);

void OpenHelpMessageOrActivate_020c4b50(ItemScreen *screen)
{
    if (func_02029f48() != 0) {
        return;
    }
    if (!func_ov077_020c8bd4(screen->work, screen, NULL, func_ov077_020c4bb0, data_ov077_020ca0fc, 1)) {
        screen->state = 2;
        func_ov077_020c58e0(screen);
        func_ov077_020c4be0(screen);
        return;
    }
    screen->state = 1;
    SetFlagGatedElementsVisible_020c9d7c(func_ov039_020bc1bc(), FALSE);
}
