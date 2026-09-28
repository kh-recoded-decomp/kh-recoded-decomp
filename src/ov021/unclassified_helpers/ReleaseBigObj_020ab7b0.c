#include "nitro/types.h"

extern void ClearSbcCallback_020188b8(void *renderObj);
extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern void func_ov021_020a9084(void *state);

void ReleaseBigObj_020ab7b0(u8 *obj)
{
    ClearSbcCallback_020188b8(obj + 0x20);
    ReleaseResourceAndDetach_0202eee8(obj);
    func_ov021_020a9084(obj + 0x104);
}
