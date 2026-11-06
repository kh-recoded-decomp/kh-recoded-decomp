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

extern u8 *gOv013PanelGlobals;
extern Overlay27Entry *FindActiveBackgroundScreenResourceById(u8 *context, int entryId);
extern Overlay27Timing *FindActiveRecordById(u8 *context, int entryId);
extern void GXS_LoadBG0Scr(Overlay27Target *dest, s32 angle, s32 extra);

void UploadOv013SubBg0ScreenEntry1(void) {
    Overlay27Entry *entry = FindActiveBackgroundScreenResourceById(gOv013PanelGlobals + 0x350, 1);
    Overlay27Timing *timing = FindActiveRecordById(gOv013PanelGlobals + 0x350, 1);
    Overlay27Target *target = entry->target;
    GXS_LoadBG0Scr(target + 1, timing->angle << 6, target->extra);
}
