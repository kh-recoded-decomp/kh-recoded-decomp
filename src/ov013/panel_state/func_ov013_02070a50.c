#include "nitro/types.h"

typedef struct Overlay27Target {
    u8 pad_00[0x8];
    s32 extra;
} Overlay27Target;

typedef struct Overlay27Entry {
    u8 pad_00[0x8];
    Overlay27Target *target;
} Overlay27Entry;

typedef struct Overlay27Timing {
    u8 pad_00[0x4];
    s16 angle;
} Overlay27Timing;

extern u8 *g_panelState_02074ce0;
extern Overlay27Entry *func_ov027_020b8558(u8 *context, int entryId);
extern Overlay27Timing *func_ov027_020b8184(u8 *context, int entryId);
extern void func_020075c0(Overlay27Target *dest, s32 angle, s32 extra);

void func_ov013_02070a50(void) {
    Overlay27Entry *entry = func_ov027_020b8558(g_panelState_02074ce0 + 0x350, 1);
    Overlay27Timing *timing = func_ov027_020b8184(g_panelState_02074ce0 + 0x350, 1);
    Overlay27Target *target = entry->target;
    func_020075c0(target + 1, timing->angle << 6, target->extra);
}
