#include "nitro/types.h"

#define reg_OS_IME (*(vu16 *)0x04000208)

typedef void *(*LayerSourceFunc)(void);

typedef struct LayerSourceTable {
    LayerSourceFunc sources[3];
} LayerSourceTable;

typedef struct LayerIdTable {
    int ids[3];
} LayerIdTable;

typedef struct RecordEntry {
    u32 word0;
    u32 word1;
    u8 pad_08[0xc];
    u32 word5;
} RecordEntry;

typedef struct EntrySummary {
    u32 word0;
    u32 word1;
    u32 word5;
} EntrySummary;

typedef struct HudContext {
    u8 pad_000[0x2f4];
    u8 unk_2F4[0x450 - 0x2f4];
    void *layerBuffers[3];
    u8 pad_45c[0x480 - 0x45c];
    u32 unk_480_0 : 8;
    u32 layersRequested : 1;
    u32 layersLoaded : 1;
    u32 unk_480_10 : 22;
    u8 pad_484[0x6e4 - 0x484];
    EntrySummary *entrySummaries;
    u16 *recordText;
    u16 *recordStrings[0x112];
} HudContext;

typedef struct HudGlobals {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_ov001_020a04c4;
extern const LayerSourceTable gMainBgScreenGetters;
extern const LayerIdTable gMainBgLayerIds;

extern void *GetSceneTagTracker(void);
extern void *func_ov001_0207123c(void);
extern s32 func_ov001_02078494(void);
extern void SetFieldMenuMode_02078360(int a, int b);
extern void func_ov035_020bc3ac(void);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void MIi_CpuCopy16(const void *src, void *dst, u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void ClearTileTableRowAndMarkDirty(void *widgets, int layer);
extern void MarkTileTableRowDirty(void *widgets, int layer);
extern void func_ov001_02078180(void);
extern int CountAssignedFieldSlots(void);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void BuildSlotLabelWindows(HudContext *context);
extern void func_020cf02c(void *object, int arg);
extern void AcquireRecordManager(void);
extern void ReleaseRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern BOOL ReleaseRecordSlot(s32 slot);
extern const u16 *GetSlotPair1AuxCursor(u32 *size);
extern RecordEntry *GetRecordSlotPair1Entry(s32 index);

static inline u16 DisableIme(void)
{
    u16 prev = reg_OS_IME;
    reg_OS_IME = 0;
    return prev;
}

static inline u16 EnableIme(void)
{
    u16 prev = reg_OS_IME;
    reg_OS_IME = 1;
    return prev;
}

void LoadHudLayersAndRecordText(void)
{
    HudContext *context = data_ov001_020a04c4.context;
    void *tracker = GetSceneTagTracker();
    LayerSourceTable sources = gMainBgScreenGetters;
    void *widgets = func_ov001_0207123c();
    LayerIdTable layers = gMainBgLayerIds;
    u16 savedIme;
    int i;
    void *buffer;
    int layer;
    u32 size;
    const u16 *text;
    u16 *cursor;
    EntrySummary *summary;
    RecordEntry *entry;

    if (!context->layersRequested || context->layersLoaded == 1) {
        return;
    }
    context->layersLoaded = 1;
    if (func_ov001_02078494() == 2) {
        SetFieldMenuMode_02078360(0, 1);
    }
    func_ov035_020bc3ac();
    savedIme = DisableIme();
    for (i = 0; i < 3; i++) {
        context->layerBuffers[i] = NNS_FndAllocFromDefaultExpHeapEx(0x800, -0x20);
        MIi_CpuCopyFast(sources.sources[i](), buffer = context->layerBuffers[i], 0x800);
        layer = layers.ids[i];
        ClearTileTableRowAndMarkDirty(widgets, layer);
        MarkTileTableRowDirty(widgets, layer);
    }
    if (savedIme) {
        EnableIme();
    }
    func_ov001_02078180();
    func_ov027_020b8230(
        tracker,
        FindActiveRecordById(tracker, CountAssignedFieldSlots() + 0x50));
    BuildSlotLabelWindows(context);
    func_020cf02c(context->unk_2F4, 0);
    AcquireRecordManager();
    AcquireRecordSlot(1, 0);
    if (context->recordText == NULL) {
        text = GetSlotPair1AuxCursor(&size);
        context->recordText = NNS_FndAllocFromDefaultExpHeapEx(size, -4);
        MIi_CpuCopy16(text, context->recordText, size);
        cursor = context->recordText;
        for (i = 0; i < 0x112; i++) {
            context->recordStrings[i] = cursor;
            while (*cursor++ != 0) {
            }
        }
        if (context->entrySummaries == NULL) {
            context->entrySummaries = NNS_FndAllocFromDefaultExpHeapEx(0xcd8, -4);
            MI_CpuFill8(context->entrySummaries, 0, 0xcd8);
            summary = context->entrySummaries;
            for (i = 0; i < 0x112; i++) {
                entry = GetRecordSlotPair1Entry(i);
                summary->word0 = entry->word0;
                summary->word1 = entry->word1;
                summary->word5 = entry->word5;
                summary++;
            }
        }
    }
    ReleaseRecordSlot(1);
    ReleaseRecordManager();
}
