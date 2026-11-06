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

extern u8 *gOv013PanelGlobals;
extern Entry *FindActiveBackgroundScreenResourceById(u8 *context, int entryId);
extern void GXS_LoadBG0Scr(void *dest, s32 value, s32 size);

void DrawOv013ListPositionCounter(s32 param1, s32 param2) {
    s32 position = 0;
    Entry *entry = FindActiveBackgroundScreenResourceById(gOv013PanelGlobals + 0x350, 3);
    GXS_LoadBG0Scr((u8 *)entry->target + 0xc, 0, entry->target->value08);

    entry = FindActiveBackgroundScreenResourceById(gOv013PanelGlobals + 0x350, 2);
    do {
        s32 row = (12 - position) * 2;
        GXS_LoadBG0Scr((u8 *)entry->target + 0xe + (param1 % 10) * 2, row + 0x80, 2);
        GXS_LoadBG0Scr((u8 *)entry->target + 0x4e + (param1 % 10) * 2, row + 0xc0, 2);
        param1 = param1 / 10;
        position = position + 1;
    } while (param1 != 0);

    position = 0;
    do {
        s32 row = (17 - position) * 2;
        GXS_LoadBG0Scr((u8 *)entry->target + 0x22 + (param2 % 10) * 2, row + 0x80, 2);
        GXS_LoadBG0Scr((u8 *)entry->target + 0x62 + (param2 % 10) * 2, row + 0xc0, 2);
        position = position + 1;
        param2 = param2 / 10;
    } while (param2 != 0);
}
