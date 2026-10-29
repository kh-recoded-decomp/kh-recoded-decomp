#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x130];
    s32 unk_130;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern void *GetSceneTagTracker(void);
extern void *FindLoadedElementById(void *tracker, u32 id);
extern void SetTagRecordArmed(void *tracker, void *entry, u32 flag);
extern void *FindActiveRecordById(void *tracker, u32 recordId);
extern void TagTracker_InvokeCallback(void *tracker, void *record);

void func_ov001_02078ac4(void)
{
    void *tracker = GetSceneTagTracker();
    FieldMenu *menu = data_ov001_020a04d0.menu;

    if (menu->unk_130 != 0) {
        SetTagRecordArmed(tracker, FindLoadedElementById(tracker, 15), 0);
        TagTracker_InvokeCallback(tracker, FindActiveRecordById(tracker, 0x24));
        menu->unk_130 = 0;
    }
}
