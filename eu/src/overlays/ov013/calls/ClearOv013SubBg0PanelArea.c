#include "nitro/types.h"

typedef struct Overlay27Timing {
    u8 pad_00[0x4];
    s16 angle;
    u8 pad_06[0xa - 0x6];
    s16 width;
    s16 height;
} Overlay27Timing;

typedef struct PanelState {
    u8 pad_00[0x98];
    u8 flags;
} PanelState;

extern PanelState *gOv013PanelGlobals;
extern Overlay27Timing *FindActiveRecordById(u8 *context, int entryId);
extern void *G2S_GetBG0ScrPtr(void);
extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);

void ClearOv013SubBg0PanelArea(void) {
    Overlay27Timing *timing = FindActiveRecordById((u8 *)gOv013PanelGlobals + 0x350, 1);
    s32 size = timing->width * timing->height * 2;
    void *dest = (u8 *)G2S_GetBG0ScrPtr() + (timing->angle << 6);
    MIi_CpuClearFast(0, dest, size);
    gOv013PanelGlobals->flags = gOv013PanelGlobals->flags & ~4;
}
