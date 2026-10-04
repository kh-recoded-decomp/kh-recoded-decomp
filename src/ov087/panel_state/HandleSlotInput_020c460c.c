#include "nitro/types.h"

typedef struct {
    int kind;
    int unk_04;
} PanelMode;

typedef struct {
    u8 pad_000[0xc];
    int scrollActive;
    u8 pad_010[0xb60];
    PanelMode modes[6];
    int modeIndex;
    int selectedSlot;
} PanelScene;

extern PanelScene *func_ov039_020bc618(void);
extern void func_ov087_020c44a4(PanelScene *scene, void *context);
extern void func_ov087_020c43c4(PanelScene *scene, void *context, int slot, BOOL immediate);

void HandleSlotInput_020c460c(void *context, u32 pressed)
{
    PanelScene *scene = func_ov039_020bc618();
    BOOL immediate = FALSE;

    if (!(pressed & 0xf0)) {
        return;
    }
    if (scene->scrollActive != 0) {
        return;
    }
    if (pressed & 0xc0) {
        immediate = TRUE;
        func_ov087_020c44a4(scene, context);
    } else if (scene->selectedSlot != 0) {
        immediate = TRUE;
    }
    func_ov087_020c43c4(scene, context, scene->selectedSlot, immediate);
}
