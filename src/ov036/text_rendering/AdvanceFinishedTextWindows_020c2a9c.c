#include "nitro/types.h"

typedef struct RecordEntry {
    s32 recordIndex;
    u8 pad_04[0x8];
    u32 flags;
} RecordEntry;

typedef struct TextWindowEntry {
    u8 pad_000[0x4];
    s32 style;
    u8 pad_008[0xa4];
    s32 page;
    s32 pageCount;
    RecordEntry nameRecord;
    u8 pad_0C4[0x4c];
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
    s32 openWindowCount;
    u8 loader[0x1c];
    s32 loaderState;
    u8 pad_6850[0x4c];
    s32 historyEnabled;
} OverlayWork;

extern OverlayWork *data_ov036_020c3844;
extern int func_ov036_020c27ec(TextWindowEntry *window);
extern void func_ov036_020c27dc(TextWindowEntry *window, int state);
extern void SetRecordEntryEnabled_020bf4fc(RecordEntry *entry, int enabled);

void AdvanceFinishedTextWindows_020c2a9c(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        TextWindowEntry *window = &data_ov036_020c3844->windows[i];

        if (func_ov036_020c27ec(window) == 7) {
            BOOL finished = FALSE;

            if (data_ov036_020c3844->historyEnabled > 0 && window->page >= window->pageCount - 1
                && data_ov036_020c3844->loaderState == 1) {
                finished = TRUE;
            }
            if (finished) {
                func_ov036_020c27dc(&data_ov036_020c3844->windows[i], 0xd);
            } else {
                func_ov036_020c27dc(&data_ov036_020c3844->windows[i], 8);
                if (data_ov036_020c3844->windows[i].style != 0xe) {
                    SetRecordEntryEnabled_020bf4fc(&data_ov036_020c3844->windows[i].nameRecord, 1);
                }
            }
        }
    }
}
