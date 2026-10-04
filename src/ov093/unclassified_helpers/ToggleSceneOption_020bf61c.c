#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xcf50];
    int optionToggle;
} SceneWork;

extern int func_ov093_020c2348(SceneWork *work);
extern void SetSlotAnimFlag_020c0310(int side, int slotIndex, int value, SceneWork *work);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void ToggleSceneOption_020bf61c(SceneWork *work)
{
    BOOL visible;

    if (func_ov093_020c2348(work) != 6) {
        return;
    }
    work->optionToggle = (work->optionToggle + 1) % 2;
    visible = TRUE;
    if (work->optionToggle == 1) {
        visible = FALSE;
    }
    SetSlotAnimFlag_020c0310(0, 2, visible, work);
    PlaySoundEffect_0204d924(0, 1);
}
