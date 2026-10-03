#include "nitro/types.h"

typedef struct TextWindowEntry {
    u8 data[0x110];
} TextWindowEntry;

typedef struct HistoryEntry {
    u8 pad_00[0x18];
    void *text;
    u8 pad_1C[0xc];
} HistoryEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
    s32 openWindowCount;
    u8 loader[0x1c];
    HistoryEntry history[2];
    s32 historyCount;
} OverlayWork;

typedef void (*TextWindowHandler)(TextWindowEntry *window);

extern OverlayWork *data_ov036_020c3844;
extern TextWindowHandler data_ov036_020c3434[];
extern int func_ov036_020c27ec(TextWindowEntry *window);
extern void func_ov036_020c27dc(TextWindowEntry *window, int state);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void func_01ff8740(int value, void *dst, u32 size);

void CloseAllTextWindows_020c2910(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        TextWindowEntry *window = &data_ov036_020c3844->windows[i];

        if (func_ov036_020c27ec(window) != 0) {
            TextWindowHandler handler;

            func_ov036_020c27dc(window, 10);
            handler = data_ov036_020c3434[func_ov036_020c27ec(window)];
            if (handler != NULL) {
                handler(window);
            }
        }
    }
    for (i = 0; i < data_ov036_020c3844->historyCount; i++) {
        HistoryEntry *entry = &data_ov036_020c3844->history[i];

        NNSi_FndFreeFromDefaultHeap_0202a1c4(entry->text);
        func_01ff8740(0, entry, sizeof(HistoryEntry));
    }
    data_ov036_020c3844->historyCount = 0;
}
