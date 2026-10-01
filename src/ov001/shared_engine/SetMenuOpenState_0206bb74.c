#include "nitro/types.h"

typedef union {
    u32 raw;
    struct {
        u32 active : 1;
        u32 visible : 1;
        u32 unk_2 : 3;
        u32 highlighted : 1;
        u32 unk_6 : 26;
    } bits;
} MenuFlags;

typedef struct {
    MenuFlags flags;
    u8 listState[0xc8];
    u8 cursorState[8];
} MenuState;

extern MenuState *data_ov001_020a0484;
extern void ResumeOrResetRequest_0206bbe4(int resume);
extern void PlaySoundEffect_0204d924(int channel, int soundId);
extern void func_ov001_0206b930(void *listState);
extern void ClearWords124And128_0206c038(void *cursorState);

void SetMenuOpenState_0206bb74(int open, BOOL withSound)
{
    MenuState *menu = data_ov001_020a0484;

    ResumeOrResetRequest_0206bbe4(open);
    if (open) {
        if (withSound) {
            menu->flags.bits.visible = TRUE;
            menu->flags.bits.active = FALSE;
            menu->flags.bits.highlighted = FALSE;
            PlaySoundEffect_0204d924(0, 5);
            return;
        }
        menu->flags.raw |= 1;
        return;
    }
    if ((menu->flags.raw & 2) && withSound) {
        PlaySoundEffect_0204d924(0, 6);
    }
    menu->flags.bits.visible = FALSE;
    menu->flags.bits.active = FALSE;
    menu->flags.bits.highlighted = FALSE;
    func_ov001_0206b930(menu->listState);
    ClearWords124And128_0206c038(menu->cursorState);
}
