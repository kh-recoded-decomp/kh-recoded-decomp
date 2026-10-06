#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x104];
    s32 unk_104;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern void DrawMenuPanelPage(FieldMenu *menu);
extern void *GetSceneTagTracker(void);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, s32 mode);

void func_ov001_02078180(void)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;

    DrawMenuPanelPage(menu);
    func_ov001_02075e10(menu, GetSceneTagTracker(), menu->unk_104);
}
