#include "nitro/types.h"

typedef struct TextWindowEntry {
    u8 data[0x110];
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
    s32 openWindowCount;
    u8 loader[0x1c];
    s32 loaderState;
    u8 pad_6850[0x4c];
    s32 historyEnabled;
    u8 pad_68a0[0x4];
    s32 cooldown;
} OverlayWork;

typedef void (*TextWindowHandler)(TextWindowEntry *window);

extern s32 data_0205fde4;
extern OverlayWork *data_ov036_020c3844;
extern TextWindowHandler data_ov036_020c3434[];
extern void FS_UnloadOverlayImage_0204f5dc(void *loader);
extern int func_ov036_020c27ec(TextWindowEntry *window);
extern void PushTextWindowHistory_020be928(void);
extern void func_ov036_020bf600(void);

int UpdateTextWindows_020be9a0(void)
{
    OverlayWork *work;
    int i;

    if (data_0205fde4 != 0) {
        return 0;
    }
    if (data_ov036_020c3844->cooldown > 0) {
        data_ov036_020c3844->cooldown--;
    }
    FS_UnloadOverlayImage_0204f5dc(data_ov036_020c3844->loader);
    work = data_ov036_020c3844;
    if (work->historyEnabled > 0) {
        TextWindowEntry *first = work->windows;

        if (work->loaderState == 1 && func_ov036_020c27ec(first) >= 0xd) {
            PushTextWindowHistory_020be928();
        }
    }
    for (i = 0; i < 3; i++) {
        TextWindowEntry *window = &data_ov036_020c3844->windows[i];
        TextWindowHandler handler = data_ov036_020c3434[func_ov036_020c27ec(window)];

        if (handler != NULL) {
            handler(window);
        }
    }
    func_ov036_020bf600();
    return 0;
}
