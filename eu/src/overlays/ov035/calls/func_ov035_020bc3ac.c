#include "nitro/types.h"

extern u32 GetSceneTagTracker(void);
extern u32 FindActiveRecordById(u32 handle, int index);
extern void func_ov027_020b8288(u32 handle, u32 value);
extern u32 FindLoadedElementById(u32 handle, int index);
extern void SetTagRecordArmed(u32 handle, u32 value, int flag);

void func_ov035_020bc3ac(void) {
    u32 handle;
    u32 value;

    handle = GetSceneTagTracker();
    value = FindLoadedElementById(handle, 1);
    SetTagRecordArmed(handle, value, 0);
    value = FindActiveRecordById(handle, 5);
    func_ov027_020b8288(handle, value);
}
