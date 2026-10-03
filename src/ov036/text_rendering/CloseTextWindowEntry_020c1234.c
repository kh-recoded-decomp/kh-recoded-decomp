#include "nitro/types.h"

typedef struct RecordEntry {
    s32 recordIndex;
    u8 pad_04[0x8];
    u32 flags;
} RecordEntry;

typedef struct TextWindowEntry {
    u8 pad_000[0x34];
    void *glyphBuffer;
    u8 pad_038[0x7c];
    RecordEntry nameRecord;
    u8 pad_0C4[0x30];
    RecordEntry bodyRecord;
    u8 pad_104[0x8];
    void *lineBuffer;
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x682c];
    s32 openWindowCount;
} OverlayWork;

extern OverlayWork *data_ov036_020c3844;
extern void SetDisplayLayersVisible_020c2768(TextWindowEntry *config, BOOL enable);
extern void SetRecordEntryEnabled_020bf4fc(RecordEntry *entry, int enabled);
extern void func_ov036_020bf61c(TextWindowEntry *window);
extern void func_ov036_020bee40(TextWindowEntry *window);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void func_ov036_020c27dc(TextWindowEntry *entry, int state);

void CloseTextWindowEntry_020c1234(TextWindowEntry *window)
{
    SetDisplayLayersVisible_020c2768(window, FALSE);
    SetRecordEntryEnabled_020bf4fc(&window->bodyRecord, 0);
    if (window->nameRecord.recordIndex != -1) {
        SetRecordEntryEnabled_020bf4fc(&window->nameRecord, 0);
    }
    func_ov036_020bf61c(window);
    func_ov036_020bee40(window);
    if (window->glyphBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(window->glyphBuffer);
        window->glyphBuffer = NULL;
    }
    if (window->lineBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(window->lineBuffer);
        window->lineBuffer = NULL;
    }
    data_ov036_020c3844->openWindowCount--;
    if (data_ov036_020c3844->openWindowCount < 0) {
        data_ov036_020c3844->openWindowCount = 0;
    }
    func_ov036_020c27dc(window, 0);
}
