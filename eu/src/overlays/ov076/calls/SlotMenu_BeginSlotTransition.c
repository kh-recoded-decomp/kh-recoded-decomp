#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotMenu {
    s32 state;
    u8 pad004[0x718 - 4];
    u8 modelAnimations[0x7bc - 0x718];
    VecFx32 modelPosition;
    u8 pad7c8[0x11ee6 - 0x7c8];
    s16 slotIndex;
    u8 pad11ee8[0x11f18 - 0x11ee8];
    s32 scrollY;
    u8 pad11f1c[0x12368 - 0x11f1c];
    fx32 originX;
    fx32 originY;
    u8 pad12370[0x49856 - 0x12370];
    u8 transitionActive;
    u8 transitionFrames;
} SlotMenu;

extern void *G2_GetBG1ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dst, u32 size);
extern BOOL PlaySoundEffect(int group, int id);
extern void func_ov076_020c7714(s32 x, s32 y, fx32 *outX, fx32 *outY);
extern int *func_01ffb2f8(void *animations, int index, int frame);

void SlotMenu_BeginSlotTransition(SlotMenu *menu)
{
    s32 y;

    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x600);
    PlaySoundEffect(1, 7);
    y = (menu->slotIndex << 6) + 32 - menu->scrollY;
    func_ov076_020c7714(72, y, &menu->originX, &menu->originY);

    menu->modelPosition.z = 0x300000;
    menu->modelPosition.x = 0x00050800;
    y += 8;
    menu->modelPosition.y = ((192 - y) << 12) - 0x800;

    /* Reset the three model animation tracks before starting the transition. */
    func_01ffb2f8(menu->modelAnimations, 2, 0);
    func_01ffb2f8(menu->modelAnimations, 4, 0);
    func_01ffb2f8(menu->modelAnimations, 0, 0);

    menu->transitionActive = 1;
    menu->transitionFrames = 25;
    menu->state = 6;
}
