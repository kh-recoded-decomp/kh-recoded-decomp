#include "nitro/types.h"
#include "nitro/fx_types.h"

#define FX_F32_TO_FX32(x) ((fx32)(((x) > 0) ? ((x) * 4096.0f + 0.5f) : ((x) * 4096.0f - 0.5f)))
#define FX_MUL_ROUND(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

typedef struct {
    u8 data[0x34];
} TextWindow;

typedef struct {
    int unk_00;
    int count;
    void *entries;
} MessageTable;

typedef struct {
    int value;
    int unk_04;
} SlotCount;

typedef struct {
    s16 itemId;
    u8 kind;
    u8 pad_03;
    u16 value;
} StatSlot;

typedef struct {
    int messageId;
    int bitIndex;
} EntryInfo;

typedef struct {
    u8 pad_00[0xc];
    u16 level;
} SelectionRecord;

typedef struct {
    u8 pad_00[0x40];
    const char *name;
} RecordEntry;

typedef struct {
    int unk_00;
    int count;
    u8 pad_08[0x24];
    int first;
} EntryList;

typedef struct {
    u8 pad_000[0x31c];
    TextWindow titleWindow;
    TextWindow listWindow;
    TextWindow headerWindow;
    TextWindow detailWindow;
    u8 pad_3ec[0xcee0 - 0x3ec];
    MessageTable messages[3];
    int selectedIndex;
    int unk_CF08;
    int statsMode;
    SlotCount slotCounts[40];
    StatSlot *slots;
    EntryList list;
} StatusMenu;

extern EntryInfo data_ov099_020c241c[];
extern const char data_ov099_020c277c[];
extern const char data_ov099_020c2784[];
extern const char data_ov099_020c27a8[];

extern void CallVirtualHandlerSlot1_02001574(TextWindow *window, int arg);
extern void FlushBufferAndRunCallback_0200153c(TextWindow *window);
extern int func_020019f4(TextWindow *window);
extern const char *func_ov027_020ba2a8(MessageTable *table, int index);
extern void func_ov099_020c0588(TextWindow *window, int x, int y, int color, int anchor, const char *text);
extern void func_ov099_020c05ec(TextWindow *window, int x, int y, int color, int shadowColor, const char *text);
extern BOOL IsEntryFlagSet_020c168c(int flagSet, int entryIndex);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern void *func_0202e060(char *dst, const char *fmt, ...);
extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern int ComputeScaledPercentPlusOne_02051134(void);
extern s32 func_020275c8(void);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern RecordEntry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern int func_ov099_020beb20(int itemId);
extern int FX_Div_01ff9c84(int numer, int denom);
extern int func_02001908(TextWindow *window, const char *text, int arg);

static inline void DrawStatRow(StatusMenu *menu, MessageTable *common, int row, int y, int bit, fx32 scale, char *lineText)
{
    const char *text;
    int itemId;
    int nameId;
    fx32 percent;
    fx32 ratio;
    int width;

    itemId = menu->slots[row].itemId;
    nameId = itemId;
    if (menu->slots[row].kind == 0xff) {
        nameId = func_ov099_020beb20(itemId);
    }
    func_ov099_020c0588(&menu->detailWindow, 0, y, 9, 0, func_ov027_020ba2a8(common, 5 + row));
    if (itemId == -1) {
        if (menu->slotCounts[menu->selectedIndex].value > 0) {
            text = func_ov027_020ba2a8(common, 10);
        } else {
            text = func_ov027_020ba2a8(common, 9);
        }
    } else if (IsGlobalPackedBitSet_02027304(bit)) {
        text = GetRecordSlotPair0Entry_02051ec8(nameId)->name;
    } else {
        text = func_ov027_020ba2a8(common, 9);
    }
    func_ov099_020c0588(&menu->detailWindow, 0x38, y, 1, 0, text);
    if (itemId == -1) {
        if (menu->slotCounts[menu->selectedIndex].value > 0) {
            text = func_ov027_020ba2a8(common, 10);
        } else {
            text = func_ov027_020ba2a8(common, 9);
        }
        func_ov099_020c0588(&menu->detailWindow, 0xd8, y, 1, 0x20, text);
    } else if (menu->slotCounts[menu->selectedIndex].value > 0) {
        ratio = FX_Div_01ff9c84(FX_F32_TO_FX32((f32)menu->slots[row].value), 0x64000) + 4;
        percent = FX_MUL_ROUND(ratio, scale);
        if (percent > 0x64000) {
            percent = 0x64000;
        }
        if (func_020275c8() == 2) {
            func_0202e060(lineText, data_ov099_020c2784, ratio, percent);
        } else {
            func_0202e060(lineText, data_ov099_020c27a8, ratio, percent);
        }
        width = func_02001908(&menu->detailWindow, lineText, 0);
        func_ov099_020c05ec(&menu->detailWindow, 0xdc - width, y, 1, 0xb, lineText);
    } else {
        func_ov099_020c0588(&menu->detailWindow, 0xd8, y, 1, 0x20, func_ov027_020ba2a8(common, 9));
    }
}

void DrawEntryStatsPanels_020bf818(int mode, StatusMenu *menu)
{
    char countText[20];
    char lineText[100];
    fx32 levelFactor;
    fx32 bonus;
    fx32 difficulty;
    fx32 scale;
    int bitBase;
    const char *text;
    MessageTable *common = &menu->messages[0];
    MessageTable *details = &menu->messages[1];
    MessageTable *names = &menu->messages[2];

    if (mode == -1 || mode == 0) {
        int entry;
        int i;
        EntryList *list;
        int y;
        int width;
        CallVirtualHandlerSlot1_02001574(&menu->titleWindow, 0);
        func_ov099_020c0588(&menu->titleWindow, 4, 2, 3, 0, func_ov027_020ba2a8(common, 0));
        FlushBufferAndRunCallback_0200153c(&menu->titleWindow);
        list = &menu->list;
        CallVirtualHandlerSlot1_02001574(&menu->listWindow, 0);
        width = func_020019f4(&menu->listWindow);
        y = 2;
        for (i = 0; i < list->count; i++) {
            entry = list->first + i;
            if (IsEntryFlagSet_020c168c(0, entry)) {
                text = func_ov027_020ba2a8(names, data_ov099_020c241c[entry].messageId);
            } else {
                text = func_ov027_020ba2a8(common, 9);
            }
            func_ov099_020c0588(&menu->listWindow, 6, y, 1, 0, text);
            y += width + 6;
        }
        FlushBufferAndRunCallback_0200153c(&menu->listWindow);
    }

    if (mode != 1 && mode != -1) {
        return;
    }

    if (menu->statsMode == 0) {
        CallVirtualHandlerSlot1_02001574(&menu->headerWindow, 0);
        func_ov099_020c0588(&menu->headerWindow, 8, 12, 3, 0, func_ov027_020ba2a8(common, 2));
        func_ov099_020c0588(&menu->headerWindow, 0xa8, 12, 9, 0x10, func_ov027_020ba2a8(common, 3));
        /* Entry bit offset lives in the second word */
        func_0202e060(countText, data_ov099_020c277c,
                      ReadGlobalPackedBits_02027348(((int *)&data_ov099_020c241c[menu->selectedIndex])[1], 0x11));
        func_ov099_020c0588(&menu->headerWindow, 0xe8, 12, 7, 0x20, countText);
        FlushBufferAndRunCallback_0200153c(&menu->headerWindow);
        CallVirtualHandlerSlot1_02001574(&menu->detailWindow, 0);
        if (IsEntryFlagSet_020c168c(0, menu->selectedIndex)) {
            func_ov099_020c0588(&menu->detailWindow, 0, 4, 1, 0,
                                func_ov027_020ba2a8(details, menu->selectedIndex));
        }
        FlushBufferAndRunCallback_0200153c(&menu->detailWindow);
        return;
    }

    levelFactor = FX_MUL_ROUND(FX_F32_TO_FX32((f32)GetOverlaySelectionRecord(0)->level), 0x400) + 0x1000;
    bonus = ComputeScaledPercentPlusOne_02051134();
    difficulty = FX_F32_TO_FX32((f32)func_020275c8());
    scale = FX_MUL_ROUND(difficulty, FX_MUL_ROUND(levelFactor, bonus));

    CallVirtualHandlerSlot1_02001574(&menu->headerWindow, 0);
    func_ov099_020c0588(&menu->headerWindow, 8, 12, 3, 0, func_ov027_020ba2a8(common, 4));
    FlushBufferAndRunCallback_0200153c(&menu->headerWindow);
    bitBase = menu->selectedIndex * 4 + 0x5c0;
    CallVirtualHandlerSlot1_02001574(&menu->detailWindow, 0);
    DrawStatRow(menu, common, 0, 0x14, bitBase, scale, lineText);
    DrawStatRow(menu, common, 1, 0x34, bitBase + 1, scale, lineText);
    DrawStatRow(menu, common, 2, 0x54, bitBase + 2, scale, lineText);
    DrawStatRow(menu, common, 3, 0x74, bitBase + 3, scale, lineText);
    FlushBufferAndRunCallback_0200153c(&menu->detailWindow);
}
