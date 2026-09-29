#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct NameBaseTable {
    int baseIndex[11];
} NameBaseTable;

typedef struct FontSlot {
    NNSG2dFont font;
    void *file;
} FontSlot;

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct ListEntry {
    u16 recordId;
    u8 pad_02[6];
} ListEntry;

typedef struct ListData {
    u8 pad_00[6];
    u16 entryCount;
    ListEntry entries[1];
} ListData;

typedef struct ListRecord {
    u8 pad_00[4];
    ListData *data;
} ListRecord;

typedef struct NameEntry {
    u8 pad_00[0x40];
    u16 *name;
} NameEntry;

typedef struct DescEntry {
    u8 pad_00[0x28];
    u16 *text;
} DescEntry;

typedef struct WorldLocation {
    u8 world;
    u8 pad_01[0xd];
    u8 room;
} WorldLocation;

typedef struct SelectionRecord {
    u8 pad_00[0x10];
    WorldLocation location;
} SelectionRecord;

typedef struct HudContext {
    u8 pad_000[0x78];
    FontSlot labelFont;
    FontSlot narrowFont;
    u8 pad_090[0x18c - 0x90];
    TextWindow titleWindow;
    TextWindow listWindow;
    void **listLines;
    u8 pad_1f8[0xb34 - 0x1f8];
    u16 *names[0x200];
    u16 *currentName;
    ListRecord *listRecord;
} HudContext;

extern const TextFrame data_ov001_0209dc14;
extern const NameBaseTable data_ov001_0209dd3c;
extern void InitTextLayerAt_020014b0(void *window, int bgLayer, void *charBase, NNSG2dFont *font, TextFrame *frame);
extern void OpenRecordManager_02051c80(void);
extern void CloseRecordManager_02051cdc(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern NameEntry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern DescEntry *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern ListRecord *CloneRecord_02051fc8(ListRecord **out, u32 id, int useTailAlloc, int heapTag);
extern SelectionRecord *GetOverlaySelectionRecord_0204f768(u32 selectionIndex);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern int LengthTerminatedHalfwords_02022a38(u16 *text);
extern u16 *copy_padded_utf16_string_02022a74(u16 *destination, u16 *source, int unitCount);
extern void *GetWord20_020019f0(void *window);
extern void *func_02001914(void *window, int selectAsCurrent, int alignFromEnd);
extern void CallVirtualHandlerSlot1_02001574(void *window, int color);
extern void func_0200160c(void *window, int x, int y, int color, int flags, const u16 *text, void *narrowFont, int maxWidth);

void LoadRecordNamesAndEntryList_0206f484(HudContext *context)
{
    TextFrame frame = data_ov001_0209dc14;
    NameBaseTable baseTable;
    ListData *list;
    NameEntry *entry;
    WorldLocation *location;
    int length;
    int i;
    u16 *text;

    InitTextLayerAt_020014b0(&context->titleWindow, 3, 0, &context->labelFont.font, &frame);
    i = 0;
    OpenRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(0, 1);
    do {
        entry = GetRecordSlotPair0Entry_02051ec8(i);
        length = LengthTerminatedHalfwords_02022a38(entry->name);
        context->names[i] = NNSi_FndAllocFromDefaultHeap_0202a178((length + 1) * 2);
        copy_padded_utf16_string_02022a74(context->names[i], entry->name, length + 1);
        i++;
    } while (i < 0x200);
    ReleaseRecordSlot_02051dfc(0);
    baseTable = data_ov001_0209dd3c;
    i = 0;
    location = &GetOverlaySelectionRecord_0204f768(0)->location;
    context->currentName = context->names[baseTable.baseIndex[location->world] + location->room];
    AcquireRecordSlot_02051d3c(3, 1);
    CloneRecord_02051fc8(&context->listRecord, GetOverlaySelectionRecord_0204f768(0)->location.world, 0, 0xe);
    ReleaseRecordSlot_02051dfc(3);
    list = context->listRecord->data;
    frame.x = 0;
    frame.y = 0xc;
    frame.width = 8;
    frame.height = 1;
    frame.charBase = 0x260;
    frame.palette = 7;
    InitTextLayerAt_020014b0(&context->listWindow, 3, 0, &context->labelFont.font, &frame);
    context->listLines = NNSi_FndAllocFromDefaultHeap_0202a178(list->entryCount * 4);
    AcquireRecordSlot_02051d3c(1, 1);
    for (; i < list->entryCount; i++) {
        if (i > 0) {
            context->listLines[i] = func_02001914(&context->listWindow, 1, 0);
        } else {
            context->listLines[i] = GetWord20_020019f0(&context->listWindow);
        }
        text = GetRecordSlotPair1Entry_02051ef4(list->entries[i].recordId)->text;
        CallVirtualHandlerSlot1_02001574(&context->listWindow, 6);
        func_0200160c(&context->listWindow, 4, 0, 4, 0x209, text, &context->narrowFont, 0x3c);
    }
    ReleaseRecordSlot_02051dfc(1);
    CloseRecordManager_02051cdc();
}
