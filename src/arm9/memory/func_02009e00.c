#include "nitro/types.h"

extern u32 func_02003b3c(void);

BOOL func_02009e00(u32 type, u32 addr, u32 flags, u32 size) {
    BOOL rangeOk;
    BOOL ok;
    u32 limit;
    u32 base;
    BOOL result = FALSE;
    BOOL gate = FALSE;

    ok = FALSE;
    if (type <= 3 && size != 0) {
        if ((addr & 0x1f) == 0) {
            rangeOk = TRUE;
            if (0x1ff8000 < addr + size && addr < 0x2000000) {
                rangeOk = FALSE;
            }
            if (rangeOk) {
                ok = TRUE;
            }
        }
    }

    if (ok) {
        ok = TRUE;
        limit = func_02003b3c();
        if (addr + size > limit) {
            base = func_02003b3c();
            if (addr < base + 0x4000) {
                ok = FALSE;
            }
        }
        if (ok) {
            gate = TRUE;
        }
    }

    if (gate && ((flags | size) & 0x1ff) == 0) {
        result = TRUE;
    }

    return result;
}
