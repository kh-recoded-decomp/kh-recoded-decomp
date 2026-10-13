#include "nitro/types.h"
#include "nitro/fx_types.h"

/* Each container owns image entries, animation slots and widget records. */
typedef struct { u8 reserved[0x647c]; } PanelObjects;
typedef struct MsgContainerHeader MsgContainerHeader;
typedef struct { u8 primaryBits[0x67], secondaryBits[0x67]; } RecordFlagSets;
typedef struct {
    u8 reserved00[0x98];
    PanelObjects mainObjects;
    PanelObjects subObjects;
    u8 reservedC990[0x4c];
    RecordFlagSets flags;
    u8 reservedCAAA[0xcb50 - 0xcaaa];
    u8 *groupEntries[0x14];
    u8 reservedCBA0[0xcf68 - 0xcba0];
    s16 images[3];
    s16 slots[3];
    s16 group;
    u8 reservedCF76[2];
    s16 index;
    s16 groupWidth;
    s16 selection;
    s16 count;
} PanelState;
typedef struct { fx32 x, y; } SlotPosition;

extern PanelState *data_ov014_0206f9a0;
extern const u8 gPanelGroupCategories[][7];
extern const char sOv014_WxcWldLanguageBarP2_0206f960[];
extern const char sOv014_WxcWldLanguageBackP2_0206f974[];
extern void func_0204f0d4(PanelObjects *, int);
extern void ObjManager_FreeSlot(PanelObjects *, int);
extern MsgContainerHeader *Msg_OpenContainerAndReadHeader(const char *, u32, BOOL);
extern int PXI_Init_0204f020(PanelObjects *, u32);
extern int PXI_Init_0204f0c8(PanelObjects *, int, int);
extern void Slot_SetMode2Bit(PanelObjects *, int, int);
extern void SetIndexedRecordPriority(PanelObjects *, int, int);
extern void IndexedRecord_SetPair(PanelObjects *, int, const SlotPosition *);
extern void ZeroHalfThenFree(void *);
extern void *FindWidgetById(PanelObjects *, int);
extern void SetEntrySlotsVisible(PanelObjects *, void *, BOOL);
extern s32 func_ov002_02069b8c(RecordFlagSets *, int, int, BOOL);
extern s32 SetRecordFlagFromTable(RecordFlagSets *, int, int, BOOL, BOOL);
extern void func_ov027_020b96c0(PanelObjects *, void *, u16);
extern int DispatchContextCommand(u32, int, int, void *);
extern s32 GetCategoryFlagState(RecordFlagSets *, int);

/* A tagged archive address and nine-bit member id identify the image file. */
static inline u32 PackImageEntry(MsgContainerHeader *archive, int fileId)
{
    return (((u32)archive + 0x8000) & 0xfffffc) << 7 |
        0x80000000 | (fileId & 0x1ff);
}

void RefreshPanelCategorySlots(void)
{
    PanelObjects *objects = &data_ov014_0206f9a0->subObjects;
    SlotPosition position;
    int i;
    int index;
    int image;
    int slot;
    MsgContainerHeader *archive;
    u32 archiveKey;
    BOOL multipleEntries;
    int category;
    int entry;
    s32 flagState;
    void *widget;

    /* Replace the selected category and its two wrapping neighbours. */
    for (i = 0; i < 3; i++) {
        slot = data_ov014_0206f9a0->slots[i];
        image = data_ov014_0206f9a0->images[i];
        if (slot != 0 || image != 0) {
            func_0204f0d4(objects, slot);
            ObjManager_FreeSlot(objects, image);
        }
    }
    archive = Msg_OpenContainerAndReadHeader(sOv014_WxcWldLanguageBarP2_0206f960, 16, 0);
    index = data_ov014_0206f9a0->index;
    image = PXI_Init_0204f020(objects, PackImageEntry(archive,
        gPanelGroupCategories[data_ov014_0206f9a0->group][index]));
    slot = PXI_Init_0204f0c8(objects, 0, image);
    Slot_SetMode2Bit(objects, slot, 1);
    SetIndexedRecordPriority(objects, slot, 200);
    position.x = 0x8000;
    position.y = 0x78000;
    IndexedRecord_SetPair(objects, slot, &position);
    data_ov014_0206f9a0->images[0] = image;
    data_ov014_0206f9a0->slots[0] = slot;
    ZeroHalfThenFree(archive);

    archive = Msg_OpenContainerAndReadHeader(sOv014_WxcWldLanguageBackP2_0206f974, 16, 0);
    index--;
    if (index < 0) index = data_ov014_0206f9a0->groupWidth - 1;
    archiveKey = PackImageEntry(archive, 0);
    image = PXI_Init_0204f020(objects, archiveKey |
        (gPanelGroupCategories[data_ov014_0206f9a0->group][index] & 0x1ff));
    slot = PXI_Init_0204f0c8(objects, 0, image);
    Slot_SetMode2Bit(objects, slot, 1);
    SetIndexedRecordPriority(objects, slot, 210);
    position.x = 0x16000;
    position.y = 0x7d000;
    IndexedRecord_SetPair(objects, slot, &position);
    data_ov014_0206f9a0->images[1] = image;
    data_ov014_0206f9a0->slots[1] = slot;

    index = data_ov014_0206f9a0->index + 1;
    if (index >= data_ov014_0206f9a0->groupWidth) index = 0;
    image = PXI_Init_0204f020(objects, archiveKey |
        (gPanelGroupCategories[data_ov014_0206f9a0->group][index] & 0x1ff));
    slot = PXI_Init_0204f0c8(objects, 0, image);
    Slot_SetMode2Bit(objects, slot, 1);
    SetIndexedRecordPriority(objects, slot, 210);
    position.x = 0x4000;
    position.y = 0x95000;
    IndexedRecord_SetPair(objects, slot, &position);
    data_ov014_0206f9a0->images[2] = image;
    data_ov014_0206f9a0->slots[2] = slot;

    /* Navigation arrows and unread-state badges use the current selection. */
    multipleEntries = data_ov014_0206f9a0->count >= 2;
    widget = FindWidgetById(objects, 3);
    SetEntrySlotsVisible(objects, widget, multipleEntries);
    widget = FindWidgetById(objects, 4);
    SetEntrySlotsVisible(objects, widget, multipleEntries);
    category = gPanelGroupCategories[data_ov014_0206f9a0->group][data_ov014_0206f9a0->index];
    entry = data_ov014_0206f9a0->groupEntries[category][data_ov014_0206f9a0->selection];
    flagState = func_ov002_02069b8c(&data_ov014_0206f9a0->flags, category, entry, TRUE);
    widget = FindWidgetById(objects, 8);
    SetEntrySlotsVisible(objects, widget, flagState != 0);
    if (flagState != 0) {
        SetRecordFlagFromTable(&data_ov014_0206f9a0->flags, category, entry, FALSE, TRUE);
        func_ov027_020b96c0(objects, widget, 1);
        if (flagState > 0) DispatchContextCommand(0x80000018, category, entry, 0);
    }
    flagState = GetCategoryFlagState(&data_ov014_0206f9a0->flags, category);
    widget = FindWidgetById(objects, 7);
    SetEntrySlotsVisible(objects, widget, flagState != 0);
    if (flagState != 0) func_ov027_020b96c0(objects, widget, (u16)(flagState <= 0));
    ZeroHalfThenFree(archive);
}
