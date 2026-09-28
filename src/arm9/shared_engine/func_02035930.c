#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
    u8 field_0a;
    u8 field_0b;
} Entry;

extern void func_020357d8(int a, void *entry, int b, int c, int d, int e, int f);
extern int func_02035414(void *sub, u32 param2, u32 param3, u32 param4);
extern u8 *g_actorRegistry_0206083c;

BOOL func_02035930(Entry *entry, u32 param2, u32 param3, u32 param4) {
    int ok;
    if ((entry->flags & 1) == 0) {
        func_020357d8(0xffff, entry, 0, 0, 0, 1, 0x20);
    }
    ok = func_02035414((u8 *)entry + 0x10, param2, param3, param4);
    if (ok != 0) {
        entry->field_0b = g_actorRegistry_0206083c[0xc2c];
        entry->flags |= 4;
        entry->field_0a = (u8)param4;
        return TRUE;
    }
    return FALSE;
}
