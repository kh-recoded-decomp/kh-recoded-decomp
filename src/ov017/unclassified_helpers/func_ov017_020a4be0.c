#include "nitro/types.h"

extern BOOL func_ov017_020a40cc(void *node);
extern void func_ov017_020a3e10(void *node);
extern void func_ov017_020a3d74(void *node, BOOL flag);
extern void func_ov017_020a40dc(void *node, void *data);
extern void func_ov017_020a423c(void *node);
extern BOOL func_ov017_020a4b68(void *record);
extern BOOL func_ov042_020bd78c();

BOOL func_ov017_020a4be0(void *context, u32 unused, void *record, void *node)
{
    BOOL result;

    result = func_ov017_020a40cc(node);
    if ((result != 0) && (result = func_ov017_020a4b68(record), result == 0)) {
        func_ov017_020a3e10(node);
        func_ov017_020a3d74(node, 1);
        func_ov017_020a40dc(node, (u8 *)context + 8);
        func_ov017_020a423c(node);
    }
    if (func_ov042_020bd78c() == 0) {
        func_ov017_020a3d74(node, 0);
        return 1;
    }
    return 0;
}
