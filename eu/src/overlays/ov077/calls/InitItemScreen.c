#include "nitro/types.h"

#pragma opt_dead_assignments off

typedef struct ItemDefinition ItemDefinition;
typedef struct ItemListPanel ItemListPanel;
typedef struct WidgetManager WidgetManager;
typedef struct Widget Widget;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u16 unknown06;
    ItemDefinition *definition;
} ItemStock;

typedef struct ScreenSprite {
    s32 x;
    s32 y;
    s32 unknown08;
    s32 animation;
    s32 unknown10;
    s32 spriteIndex;
} ScreenSprite;

typedef struct ItemScreen {
    s32 panelFileId;
    s32 frameFileId;
    u8 unknown00008[0x14 - 8];
    /* The shared panel starts here and also owns the stock arrays below. */
    u8 panelHeader[0x80c - 0x14];
    ItemStock stocks[512 + 600];
    u8 unknown03c2c[0x11c28 - 0x3c2c];
    u16 panelValue11c28;
    u16 panelValue11c2a;
    u8 unknown11c2c[0x11ed0 - 0x11c2c];
    s32 mode;
    ScreenSprite sprites[12];
    s32 state;
    s32 slot;
    u8 unknown11ffc[0x14d04 - 0x11ffc];
    ItemStock *lastStock;
    ItemStock *equipped;
    u8 unknown14d0c[0x14d2c - 0x14d0c];
} ItemScreen;

typedef struct ItemScreenGlobals {
    ItemScreen *screen;
    u32 hintColors[2];
} ItemScreenGlobals;

typedef struct SaveState {
    u8 unknown0000[0x2db4];
    u16 partySlots[8];
} SaveState;

#define ITEM_OFFSET(type, member) ((u32)&((type *)0)->member)
typedef char ItemStockSizeCheck[sizeof(ItemStock) == 12 ? 1 : -1];
typedef char ScreenSpriteSizeCheck[sizeof(ScreenSprite) == 24 ? 1 : -1];
typedef char ItemScreenSizeCheck[sizeof(ItemScreen) == 0x14d2c ? 1 : -1];
typedef char ItemScreenGlobalsSizeCheck[sizeof(ItemScreenGlobals) == 12 ? 1 : -1];
typedef char ItemStocksOffsetCheck[ITEM_OFFSET(ItemScreen, stocks) == 0x80c ? 1 : -1];
typedef char ItemPanelValueOffsetCheck[ITEM_OFFSET(ItemScreen, panelValue11c28) == 0x11c28 ? 1 : -1];
typedef char ItemModeOffsetCheck[ITEM_OFFSET(ItemScreen, mode) == 0x11ed0 ? 1 : -1];
typedef char ItemStateOffsetCheck[ITEM_OFFSET(ItemScreen, state) == 0x11ff4 ? 1 : -1];
typedef char ItemSlotOffsetCheck[ITEM_OFFSET(ItemScreen, slot) == 0x11ff8 ? 1 : -1];
typedef char ItemEquippedOffsetCheck[ITEM_OFFSET(ItemScreen, equipped) == 0x14d08 ? 1 : -1];
typedef char SavePartySlotsOffsetCheck[ITEM_OFFSET(SaveState, partySlots) == 0x2db4 ? 1 : -1];
#undef ITEM_OFFSET

extern ItemScreenGlobals data_ov077_020ca3a0;
extern SaveState *data_0205fe0c;
extern const char sOv077_UiMenuEqumtxP2_020ca2f0[];
extern const char sOv077_UiMenuLanguageEqumtxP2_020ca304[];
extern void MI_CpuFill8(void *destination, int value, u32 size);
extern void ItemListPanel_Create(ItemListPanel *panel, int recordIndex, void (*callback)(void));
extern void func_ov077_020c5f7c(void);
extern WidgetManager *func_ov039_020bc1dc(void);
extern Widget *FindWidgetById(WidgetManager *manager, int id);
extern void SetEntrySlotsVisible(WidgetManager *manager, Widget *widget, BOOL visible);
extern s32 Msg_OpenContainerAndReadHeader(const char *path, int heap, int mode);
extern void SetupItemScreenBackgrounds(ItemScreen *screen);
extern void InitScreenSpriteSlots(ItemScreen *screen);
extern void UpdateItemCountDigits(ItemScreen *screen);
extern void DrawPartySlotLabel(ItemScreen *screen, int slot);

BOOL InitItemScreen(ItemScreen *screen)
{
    WidgetManager *manager;
    int slot;
    u16 equippedItem;

    MI_CpuFill8(screen, 0, sizeof(*screen));
    data_ov077_020ca3a0.screen = screen;
    *(vu16 *)0x04000304 &= ~0x8000;
    ItemListPanel_Create((ItemListPanel *)screen->panelHeader, 2, func_ov077_020c5f7c);
    screen->mode = 0;
    screen->panelValue11c28 = 2;
    screen->panelValue11c2a = 2;

    manager = func_ov039_020bc1dc();
    SetEntrySlotsVisible(manager, FindWidgetById(manager, 6), FALSE);
    SetEntrySlotsVisible(manager, FindWidgetById(manager, 0), FALSE);
    screen->slot = 0;
    screen->panelFileId = Msg_OpenContainerAndReadHeader(sOv077_UiMenuEqumtxP2_020ca2f0, 14, 0);
    screen->frameFileId = Msg_OpenContainerAndReadHeader(sOv077_UiMenuLanguageEqumtxP2_020ca304, 14, 0);
    SetupItemScreenBackgrounds(screen);
    InitScreenSpriteSlots(screen);
    UpdateItemCountDigits(screen);
    for (slot = 0; slot < 6; ++slot) {
        DrawPartySlotLabel(screen, slot);
    }

    screen->state = 0;
    equippedItem = data_0205fe0c->partySlots[0];
    screen->equipped = &screen->stocks[equippedItem];
    return TRUE;
}
