#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x104];
    s32 unk_104;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern void func_ov001_020769f4(FieldMenu *menu);
extern void *GetSceneTagTracker_020711b0(void);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, s32 mode);

void func_ov001_02078180(void)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;

    func_ov001_020769f4(menu);
    func_ov001_02075e10(menu, GetSceneTagTracker_020711b0(), menu->unk_104);
}
