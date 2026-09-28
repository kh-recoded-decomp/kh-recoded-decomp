#include "nitro/types.h"

extern u32 func_ov027_020ba1d8();
extern void func_ov025_020b6ab8(u32 entry, u32 tag, u32 field);
extern void func_ov027_020ba1e0(u32 owner, u32 flag);

void ApplyTagAndMarkEntryReady_020b6c0c(u32 owner, u32 entry) {
    u32 tag = func_ov027_020ba1d8();
    func_ov025_020b6ab8(entry, tag, *(u32 *)(entry + 0xc));
    func_ov027_020ba1e0(owner, 1);
}
