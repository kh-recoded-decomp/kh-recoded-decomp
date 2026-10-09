#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

#define REG_DISPCNT (*(vu32 *)0x04000000)

typedef struct {
    u8 pad_00[4];
    u16 width;
    u16 height;
    u8 pad_08[8];
    fx32 x;
    fx32 y;
    u8 pad_18[8];
    int frame;
    u8 visible;
    u8 pad_25;
    u8 alpha : 5;
    u8 pad_26_5 : 3;
    u8 pad_27[5];
} PopupEntry;

typedef struct {
    u8 pad_00[0x2c];
    int scrollRow;
    u8 pad_30[0x1c];
} ScrollList;

typedef struct {
    u8 pad_000[0x3ec];
    int popupRows[(0x414 - 0x3ec) / 4];
} EntryLayout;

typedef struct {
    int selectedEntry;
    u8 pad_0004[0x14];
    int fileBase;
    u8 pad_001c[0x150 - 0x1c];
    void *backgroundBuffer;
    u8 pad_0154[0x180 - 0x154];
    ScrollList lists[2];
    u8 pad_0218[0xce08 - 0x218];
    EntryLayout layouts[8];
    PopupEntry popups[10];
    int popupCount;
    u8 pad_f064[0xf070 - 0xf064];
    int transitionState;
} MenuScene;

typedef struct {
    int popupIds[10];
    int popupCount;
    u8 pad_2c[8];
} EntryPopupTable;

extern MenuScene *g_menuScene_020c2520;
extern EntryPopupTable data_ov097_020c2124[];
extern u32 data_ov097_020c1f1c[];
extern BOOL IsEntryFlagSet_020c1474(int flagSet, int entryIndex);
extern void SetEntryFlag_020c14a0(int flagSet, int entryIndex);
extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void LoadEntryBackground_020bf85c(MenuScene *scene);
extern void ReleasePopupEntries_020c0d20(MenuScene *scene);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void func_02013d74(void);
extern void TickPanelSlotAnimation_020c020c(int listIndex, int slotIndex, int frames, MenuScene *scene);
extern BOOL func_ov097_020c1844(PopupEntry *slot, u32 fileId);
extern void func_ov097_020c1558(int value, MenuScene *scene);

#define ROW_TO_FX32(row) ((fx32)((float)(row) > 0 ? 0.5f + 4096.0f * (float)(row) : 4096.0f * (float)(row) - 0.5f))

void TickEntryTransition_020c1580(void)
{
    MenuScene *scene = g_menuScene_020c2520;
    int row;
    int entryIndex;
    u32 plane;
    int i;
    EntryPopupTable *table;
    PopupEntry *popup;

    switch (scene->transitionState) {
    case 0:
        if (IsEntryFlagSet_020c1474(0, 1)) {
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1600;
        }
        if (scene->backgroundBuffer != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(scene->backgroundBuffer);
            scene->backgroundBuffer = NULL;
        }
        LoadEntryBackground_020bf85c(scene);
        ReleasePopupEntries_020c0d20(scene);
        NNS_GfdResetFrmTexVramState_0201391c();
        func_02013d74();
        scene->popupCount = 0;
        plane = (REG_DISPCNT & 0x1f00) >> 8;
        if (IsEntryFlagSet_020c1474(0, scene->selectedEntry)) {
            plane |= 0x10;
        } else {
            plane &= ~0x10;
        }
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | (plane << 8);
        entryIndex = scene->selectedEntry;
        if (IsEntryFlagSet_020c1474(1, entryIndex)) {
            SetEntryFlag_020c14a0(2, entryIndex);
            SetGlobalPackedBit_02027320(entryIndex + 0x1262);
        }
        i = 0;
        do {
            TickPanelSlotAnimation_020c020c(0, i + 3, IsEntryFlagSet_020c1474(2, scene->lists[0].scrollRow + i) != FALSE, scene);
            i++;
        } while (i < 8);
        scene->transitionState++;
    case 1:
        popup = &scene->popups[scene->popupCount];
        entryIndex = scene->selectedEntry;
        table = &data_ov097_020c2124[entryIndex];
        func_ov097_020c1844(popup, ((scene->fileBase + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (data_ov097_020c1f1c[table->popupIds[scene->popupCount]] & 0x1ff));
        popup->frame = 0;
        popup->visible = 1;
        popup->alpha = 0x1f;
        popup->width = 0x80;
        popup->height = 0x68;
        popup->x = 0x80000;
        row = scene->layouts[entryIndex].popupRows[scene->popupCount];
        popup->y = ROW_TO_FX32(row);
        scene->popupCount++;
        if (scene->popupCount >= table->popupCount) {
            scene->transitionState++;
        }
        break;
    case 2:
        plane = (REG_DISPCNT & 0x1f00) >> 8;
        REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((plane | 1) << 8);
        func_ov097_020c1558(0, scene);
        break;
    }
}
