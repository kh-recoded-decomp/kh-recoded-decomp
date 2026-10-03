#include "nitro/types.h"

typedef struct TextWindowEntry {
    u8 data[0x110];
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
} OverlayWork;

extern OverlayWork *data_ov036_020c3844;
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void func_01ff8740(int value, void *dst, u32 size);
extern void func_ov036_020c27dc(TextWindowEntry *entry, int state);

void PushTextWindowHistory_020be928(void)
{
    func_01ff878c(&data_ov036_020c3844->windows[1], &data_ov036_020c3844->windows[2], sizeof(TextWindowEntry));
    func_01ff878c(&data_ov036_020c3844->windows[0], &data_ov036_020c3844->windows[1], sizeof(TextWindowEntry));
    func_01ff8740(0, &data_ov036_020c3844->windows[0], sizeof(TextWindowEntry));
    func_ov036_020c27dc(&data_ov036_020c3844->windows[0], 1);
}
