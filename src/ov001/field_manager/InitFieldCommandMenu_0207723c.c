#include "nitro/types.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 unk_04;
    u16 unk_06;
    u16 height;
    u16 unk_0a;
    u16 unk_0c;
    u16 unk_0e;
} TextFrame;

typedef struct TextCell {
    u8 pad_00[0x24];
    void *pixels;
} TextCell;

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct PackedFileView {
    u32 words[3];
} PackedFileView;

typedef struct NNSFndList {
    void *headObject;
    void *tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;

typedef struct CommandGauge {
    u32 startTick;
    u32 duration;
    s32 owner;
    s32 recordId;
    s32 kind;
    s32 linkB;
    s32 linkA;
    TextCell *art;
    TextCell *linkArt;
    s32 linked;
    u16 flags;
    u16 repeat;
    s32 ready;
    u8 pad_30[0xc];
} CommandGauge;

typedef struct CommandRecord {
    u8 pad_00[4];
    s32 linkId;
    s32 linkA;
    s32 linkB;
    s32 kind;
    u8 pad_14[8];
    u16 cooldown;
    u8 pad_1e[0xa];
    int nameId;
} CommandRecord;

typedef struct SelectionSlot {
    s16 recordId;
    s16 nameIndex;
    u8 repeat;
    u8 bonusKind;
    u8 pad_06[6];
} SelectionSlot;

typedef struct SelectionSlots {
    SelectionSlot slots[16];
    u32 names[16];
    s32 count;
} SelectionSlots;

typedef struct SelectionRecord {
    u8 pad_000[0x2c];
    SelectionSlots table;
    s16 equippedId;
} SelectionRecord;

typedef struct PlayerFlagRecord {
    s16 id;
    u8 pad_02[2];
    u8 repeat;
    u8 bonusKind;
} PlayerFlagRecord;

typedef struct FieldMenu {
    TextLayer gaugeLayer;
    TextLayer textLayer;
    u8 pad_068[0xc];
    TextCell *cells[14];
    CommandGauge *primary;
    CommandGauge *secondary;
    CommandGauge *tertiary;
    NNSFndList itemList;
    s32 rowCapacity;
    s32 visibleCount;
    s32 rowCount;
    s32 primaryCount;
    s32 readyCount;
    s32 itemCount;
    s32 tertiaryCount;
    void *blankTiles;
    void *frameTiles;
    u8 pad_0e8[0x10];
    s32 itemCursor;
    u8 pad_0fc[8];
    s32 mode;
} FieldMenu;

extern TextFrame data_ov001_0209deb0;
extern const u16 data_ov001_0209eee0[];

extern void *GetSceneFont_020711bc(void);
extern SelectionRecord *func_0204f768(int index);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int alignment);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff878c(const void *src, void *dst, u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern BOOL AcquireRecordManager_02051c80(void);
extern void ReleaseRecordManager_02051cdc(void);
extern int AcquireRecordSlot_02051d3c(int slot, int param);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern int func_ov001_0207123c(void);
extern int UpdateWidgetLayerDefault_020b9df0(int layer, int mode);
extern unsigned int MakePrimaryVramKey_02073634(unsigned int slot);
extern void LoadPackedFileView_020ba25c(PackedFileView *view, u32 fileId, BOOL fromTail);
extern void FreePointerIfSet_020ba294(PackedFileView *view);
extern BOOL InitTextLayerAt_020014b0(TextLayer *layer, int index, u16 *screenBase, void *font, TextFrame *frame);
extern TextCell *GetWord20_020019f0(TextLayer *layer);
extern TextCell *func_02001914(TextLayer *layer, int a, int b);
extern void func_ov001_02076a54(FieldMenu *menu, PackedFileView *view, int index);
extern CommandRecord *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern void DrawTextAnchored_020015a0(TextLayer *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void *GetFieldFont1_020711c8(void);
extern void func_0200160c(TextLayer *layer, u32 x, u32 y, u32 color, u32 flags, int value, void *font, u32 width);
extern void SelectListNodeOrFirst_020019b8(TextLayer *layer, TextCell *target);
extern void Text_UploadTileBuffer_02001520(TextLayer *layer);
extern BOOL func_ov001_02077148(FieldMenu *menu, CommandRecord *record);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern BOOL IsFieldFlag13OrSessionFlagSet_020728e4(void);
extern CommandGauge *CycleMenuEntry_02075348(FieldMenu *menu, int index, int direction, int *outIndex);
extern void StartCommandCooldownGauge_02076b80(FieldMenu *menu, CommandGauge *gauge, u32 owner, s32 recordId, u16 repeat, u8 bonusKind, u8 bonusPercent);
extern int GetFieldSlotValue_020716c4(int index);
extern void *GetSceneTagTracker_020711b0(void);
extern void func_0201288c(NNSFndList *list, u16 offset);
extern PlayerFlagRecord *GetPlayerFlagRecord_0205036c(int index);
extern void AppendIntrusiveListObject_020128d0(NNSFndList *list, CommandGauge *object);
extern void func_ov001_02075e10(FieldMenu *menu, void *tracker, int arg);
extern void DrawFieldSlotCell_02076a9c(FieldMenu *panel, FieldMenu *layer, CommandGauge *cell, PackedFileView *messages, int slot);
extern BOOL IsModeSetOrFlag370aClear_0207259c(void);

static inline void SetupLinkedGauge(FieldMenu *menu, CommandGauge *gauge, s32 linkId)
{
    CommandRecord *linked = GetRecordSlotPair1Entry_02051ef4(linkId);

    gauge->duration = linked->cooldown << 1;
    gauge->linkArt = func_02001914(&menu->gaugeLayer, 1, 0);
    func_01ff878c(menu->blankTiles, gauge->linkArt->pixels, 0x200);
    func_0200160c(&menu->gaugeLayer, 0, 4, 2, 0, linked->nameId, GetFieldFont1_020711c8(), 0x38);
}

void InitFieldCommandMenu_0207723c(FieldMenu *menu, u8 *tiles)
{
    TextFrame frame = data_ov001_0209deb0;
    PackedFileView view;
    PackedFileView slotView;
    SelectionSlots *slots;
    void *font;
    CommandRecord *record;
    BOOL hasLinkA;
    BOOL hasLinkB;
    void *tracker;
    PlayerFlagRecord *flag;
    BOOL found;
    int repeat;
    int itemIndex;
    int slotIndex;
    int layer;
    int index;
    int total;
    int ready;
    int rows;
    int row;
    CommandRecord *equipped;
    CommandRecord *counted;
    CommandGauge *gauge;
    SelectionSlot *slot;
    u32 size;

    font = GetSceneFont_020711bc();
    slots = &func_0204f768(0)->table;
    menu->blankTiles = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x200, 0x20);
    menu->frameTiles = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x200, 0x20);
    func_01ff878c(tiles, menu->blankTiles, 0x200);
    func_01ff878c(tiles + 0x200, menu->frameTiles, 0x200);
    AcquireRecordManager_02051c80();
    AcquireRecordSlot_02051d3c(1, 1);
    layer = UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), 0xb);
    LoadPackedFileView_020ba25c(&view, MakePrimaryVramKey_02073634(1), 1);
    InitTextLayerAt_020014b0(&menu->textLayer, 3, (u16 *)layer, font, &frame);
    menu->cells[0] = GetWord20_020019f0(&menu->textLayer);
    func_ov001_02076a54(menu, &view, 0);
    for (index = 1; index < 13; index++) {
        menu->cells[index] = func_02001914(&menu->textLayer, 1, 0);
        func_ov001_02076a54(menu, &view, index);
    }
    menu->cells[index] = func_02001914(&menu->textLayer, 1, 0);
    func_01ff878c(menu->frameTiles, menu->cells[13]->pixels, 0x200);
    equipped = GetRecordSlotPair1Entry_02051ef4(func_0204f768(0)->equippedId);
    if (equipped == NULL) {
        DrawTextAnchored_020015a0(&menu->textLayer, 0, 4, 4, 0, data_ov001_0209eee0);
    } else {
        func_0200160c(&menu->textLayer, 0, 4, 4, 0, equipped->nameId, GetFieldFont1_020711c8(), 0x38);
    }
    FreePointerIfSet_020ba294(&view);
    SelectListNodeOrFirst_020019b8(&menu->textLayer, menu->cells[0]);
    Text_UploadTileBuffer_02001520(&menu->textLayer);

    total = 0;
    ready = 0;
    for (index = 0; index < slots->count; index++) {
        counted = GetRecordSlotPair1Entry_02051ef4(slots->slots[index].recordId);
        if (counted->kind != 5) {
            total++;
            if (!func_ov001_02077148(menu, counted)) {
                ready++;
            }
        }
    }
    rows = 3;
    if (total > 3) {
        rows = total;
    }
    if (!IsFieldFlag10Set_020728c4() && !IsHudFlag7Set_020725bc()) {
        menu->primaryCount = total;
        menu->visibleCount = total;
        menu->readyCount = ready;
    } else {
        menu->primaryCount = 0;
        menu->visibleCount = 0;
    }
    menu->rowCount = rows;
    menu->rowCapacity = rows;
    frame.x = 0;
    slotIndex = 0;
    frame.y = 0;
    frame.height += 0x10;
    size = rows * sizeof(CommandGauge);
    menu->primary = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    func_01ff8830(menu->primary, 0, size);
    InitTextLayerAt_020014b0(&menu->gaugeLayer, 3, NULL, font, &frame);

    row = 0;
    for (; slotIndex < slots->count; slotIndex++) {
        slot = &slots->slots[slotIndex];
        record = GetRecordSlotPair1Entry_02051ef4(slot->recordId);
        if (record->kind == 5) {
            continue;
        }
        gauge = CycleMenuEntry_02075348(menu, row, 1, NULL);
        if (slotIndex == 0) {
            gauge->art = GetWord20_020019f0(&menu->gaugeLayer);
        } else {
            gauge->art = func_02001914(&menu->gaugeLayer, 1, 0);
        }
        if (!IsFieldFlag10Set_020728c4() && !IsHudFlag7Set_020725bc()) {
            StartCommandCooldownGauge_02076b80(menu, gauge, slotIndex, slot->recordId, slot->repeat, slot->bonusKind, slot->repeat);
            if (func_ov001_02077148(menu, record)) {
                gauge->ready = TRUE;
            } else {
                gauge->ready = FALSE;
            }
        } else {
            StartCommandCooldownGauge_02076b80(menu, gauge, slotIndex, slot->recordId, 0, slot->bonusKind, slot->repeat);
            gauge->flags |= 1;
        }
        gauge->linkA = -1;
        gauge->linkB = -1;
        gauge->startTick = slots->names[slot->nameIndex];
        if (IsFieldFlag8Set_020728a4()) {
            gauge->linkB = record->linkId;
            if (record->linkId != -1) {
                record = GetRecordSlotPair1Entry_02051ef4(record->linkId);
                gauge->duration = record->cooldown;
                gauge->flags |= 0x10;
            }
        }
        if (IsFieldFlag13OrSessionFlagSet_020728e4()) {
            hasLinkA = FALSE;
            hasLinkB = FALSE;
            gauge->linkA = record->linkA;
            gauge->linkB = record->linkB;
            if (gauge->linkA != -1) {
                SetupLinkedGauge(menu, gauge, gauge->linkA);
            } else if (gauge->linkB != -1) {
                SetupLinkedGauge(menu, gauge, gauge->linkB);
            }
            if (GetFieldSlotValue_020716c4(0) == 2 || GetFieldSlotValue_020716c4(1) == 2) {
                hasLinkA = TRUE;
            }
            if (GetFieldSlotValue_020716c4(0) == 3 || GetFieldSlotValue_020716c4(1) == 3) {
                hasLinkB = TRUE;
            }
            if (gauge->kind == 3) {
                gauge->linked = 0;
                gauge->flags |= 4;
            } else if ((hasLinkA && gauge->linkA != -1) || (hasLinkB && gauge->linkB != -1)) {
                gauge->linked = 1;
                gauge->flags |= 4;
            } else {
                gauge->linked = 0;
                gauge->flags &= ~4;
            }
        }
        row++;
    }
    for (; row < 3; row++) {
        gauge = CycleMenuEntry_02075348(menu, row, 1, NULL);
        if (row == 0) {
            gauge->art = GetWord20_020019f0(&menu->gaugeLayer);
        } else {
            gauge->art = func_02001914(&menu->gaugeLayer, 1, 0);
        }
        StartCommandCooldownGauge_02076b80(menu, gauge, row, -1, 0, slots->slots[row].bonusKind, slots->slots[row].repeat);
    }

    if (IsFieldFlag8Set_020728a4()) {
        tracker = GetSceneTagTracker_020711b0();
        found = FALSE;
        func_0201288c(&menu->itemList, 0x30);
        menu->mode = 1;
        menu->secondary = NNSi_FndAllocFromDefaultHeap_0202a178(15 * sizeof(CommandGauge));
        func_01ff8830(menu->secondary, 0, 15 * sizeof(CommandGauge));
        menu->itemCursor = found;
        menu->itemCount = found;
        for (itemIndex = 0; itemIndex < 14; itemIndex++) {
            CommandGauge *item = &menu->secondary[itemIndex];
            item->art = func_02001914(&menu->gaugeLayer, 1, 0);
            repeat = 0;
            for (index = 0; index < 8; index++) {
                flag = GetPlayerFlagRecord_0205036c(index);
                if (flag->id == itemIndex + 0xcb) {
                    repeat = flag->repeat;
                    break;
                }
            }
            if (index == 8) {
                index = 0xffff;
            }
            StartCommandCooldownGauge_02076b80(menu, item, index, itemIndex + 0xcb, repeat, flag->bonusKind, flag->repeat);
            if (item->recordId != 0xffff && item->repeat != 0) {
                menu->itemCount++;
                item->flags &= ~8;
                item->flags |= 1;
                AppendIntrusiveListObject_020128d0(&menu->itemList, item);
                if (!found) {
                    found = TRUE;
                }
            } else {
                item->flags |= 8;
            }
        }
        gauge = CycleMenuEntry_02075348(menu, 14, 1, NULL);
        gauge->art = func_02001914(&menu->gaugeLayer, 1, 0);
        StartCommandCooldownGauge_02076b80(menu, gauge, 14, -1, 0, flag->bonusKind, flag->repeat);
        menu->mode = 0;
        func_ov001_02075e10(menu, tracker, 0);
        menu->tertiary = NNSi_FndAllocFromDefaultHeap_0202a178(3 * sizeof(CommandGauge));
        func_01ff8830(menu->tertiary, 0, 3 * sizeof(CommandGauge));
        LoadPackedFileView_020ba25c(&slotView, MakePrimaryVramKey_02073634(0), 1);
        for (index = 0; index < 3; index++) {
            gauge = &menu->tertiary[index];
            gauge->owner = -1;
            gauge->art = func_02001914(&menu->gaugeLayer, 1, 0);
            DrawFieldSlotCell_02076a9c(menu, menu, gauge, &slotView, index);
        }
        FreePointerIfSet_020ba294(&slotView);
    }
    if (!IsModeSetOrFlag370aClear_0207259c()) {
        for (index = 0; index < menu->primaryCount; index++) {
            gauge = &menu->primary[index];
            if (gauge->kind != 3) {
                gauge->startTick = gauge->duration;
            }
        }
    }
    ReleaseRecordSlot_02051dfc(1);
    ReleaseRecordManager_02051cdc();
}
