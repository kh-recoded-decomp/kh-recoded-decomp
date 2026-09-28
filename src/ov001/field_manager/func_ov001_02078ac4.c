#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 unk_130;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern void *GetSceneTagTracker_020711b0(void);
extern void *func_ov027_020b8390(void *tracker, u32 id);
extern void func_ov027_020b83e8(void *tracker, void *entry, u32 flag);
extern void *FindActiveRecordById_020b8184(void *tracker, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);

void func_ov001_02078ac4(void)
{
    void *tracker = GetSceneTagTracker_020711b0();
    FieldMenu *menu = data_ov001_020a04b0.menu;

    if (menu->unk_130 != 0) {
        func_ov027_020b83e8(tracker, func_ov027_020b8390(tracker, 15), 0);
        TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x24));
        menu->unk_130 = 0;
    }
}
