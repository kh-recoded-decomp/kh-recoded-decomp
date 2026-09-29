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

extern HudGlobals data_ov001_020a04a4;
extern const LayerSourceTable data_ov001_0209ecc0;
extern const LayerIdTable data_ov001_0209db94;

extern void *GetSceneTagTracker_020711b0(void);
extern void *func_ov001_0207123c(void);
extern s32 func_ov001_02078494(void);
extern void func_ov001_02078360(int a, int b);
extern void func_ov035_020bc38c(void);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void func_ov027_020b9d18(void *widgets, int layer);
extern void func_ov027_020b9e00(void *widgets, int layer);
extern void func_ov001_02078180(void);
extern int CountAssignedFieldSlots_0207169c(void);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void func_ov001_0206f858(HudContext *context);
extern void func_020cf00c(void *object, int arg);
extern void OpenRecordManager_02051c80(void);
extern void CloseRecordManager_02051cdc(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern const u16 *GetSlotPair1AuxCursor_02051f20(u32 *size);
extern RecordEntry *GetRecordSlotPair1Entry_02051ef4(s32 index);

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

void LoadHudLayersAndRecordText_0207292c(void)
{
    HudContext *context = data_ov001_020a04a4.context;
    void *tracker = GetSceneTagTracker_020711b0();
    LayerSourceTable sources = data_ov001_0209ecc0;
    void *widgets = func_ov001_0207123c();
    LayerIdTable layers = data_ov001_0209db94;
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
        func_ov001_02078360(0, 1);
    }
    func_ov035_020bc38c();
    savedIme = DisableIme();
    for (i = 0; i < 3; i++) {
        context->layerBuffers[i] = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x800, -0x20);
        func_01ff878c(sources.sources[i](), buffer = context->layerBuffers[i], 0x800);
        layer = layers.ids[i];
        func_ov027_020b9d18(widgets, layer);
        func_ov027_020b9e00(widgets, layer);
    }
    if (savedIme) {
        EnableIme();
    }
    func_ov001_02078180();
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, CountAssignedFieldSlots_0207169c() + 0x50));
    func_ov001_0206f858(context);
    func_020cf00c(context->unk_2F4, 0);
    OpenRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(1, 0);
    if (context->recordText == NULL) {
        text = GetSlotPair1AuxCursor_02051f20(&size);
        context->recordText = NNSi_FndAllocFromDefaultHeapEx_0202a19c(size, -4);
        func_01ff869c(text, context->recordText, size);
        cursor = context->recordText;
        for (i = 0; i < 0x112; i++) {
            context->recordStrings[i] = cursor;
            while (*cursor++ != 0) {
            }
        }
        if (context->entrySummaries == NULL) {
            context->entrySummaries = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0xcd8, -4);
            func_01ff8830(context->entrySummaries, 0, 0xcd8);
            summary = context->entrySummaries;
            for (i = 0; i < 0x112; i++) {
                entry = GetRecordSlotPair1Entry_02051ef4(i);
                summary->word0 = entry->word0;
                summary->word1 = entry->word1;
                summary->word5 = entry->word5;
                summary++;
            }
        }
    }
    ReleaseRecordSlot_02051dfc(1);
    CloseRecordManager_02051cdc();
}
