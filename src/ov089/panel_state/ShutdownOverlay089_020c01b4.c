#include "nitro/types.h"

extern void *func_ov039_020bc1bc(void);
extern void func_ov027_020b9098(void *panel, u32 value);
extern void func_ov089_020bf488(void *menu);
extern void func_ov089_020bf950(void *menu);
extern void func_ov089_020bfad0(void *menu);
extern void func_ov089_020bf35c(void *menu);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);

void ShutdownOverlay089_020c01b4(void *menu)
{
    func_ov027_020b9098(func_ov039_020bc1bc(), 0);
    func_ov089_020bf488(menu);
    func_ov089_020bf950(menu);
    func_ov089_020bfad0(menu);
    func_ov089_020bf35c(menu);
    ReleaseRecordSlot_02051dfc(2);
}
