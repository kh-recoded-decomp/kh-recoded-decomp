#include "nitro/types.h"

typedef struct Entry Entry;

typedef struct Target {
    u8 pad_00[0x8];
    s32 value08;
} Target;

struct Entry {
    u8 pad_00[0x8];
    Target *target;
};

extern u8 *g_panelState_02074ce0;
extern Entry *func_ov027_020b8558(u8 *context, int entryId);
extern void func_020075c0(void *dest, s32 value, s32 size);

void func_ov013_02070b78(s32 param1, s32 param2) {
    s32 position = 0;
    Entry *entry = func_ov027_020b8558(g_panelState_02074ce0 + 0x350, 3);
    func_020075c0((u8 *)entry->target + 0xc, 0, entry->target->value08);

    entry = func_ov027_020b8558(g_panelState_02074ce0 + 0x350, 2);
    do {
        s32 row = (12 - position) * 2;
        func_020075c0((u8 *)entry->target + 0xe + (param1 % 10) * 2, row + 0x80, 2);
        func_020075c0((u8 *)entry->target + 0x4e + (param1 % 10) * 2, row + 0xc0, 2);
        param1 = param1 / 10;
        position = position + 1;
    } while (param1 != 0);

    position = 0;
    do {
        s32 row = (17 - position) * 2;
        func_020075c0((u8 *)entry->target + 0x22 + (param2 % 10) * 2, row + 0x80, 2);
        func_020075c0((u8 *)entry->target + 0x62 + (param2 % 10) * 2, row + 0xc0, 2);
        position = position + 1;
        param2 = param2 / 10;
    } while (param2 != 0);
}
