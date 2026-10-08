#include "nitro/types.h"

typedef struct TouchState {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u16 state;
} TouchState;

typedef struct StatusMenu StatusMenu;

typedef int (*PageFunc)(StatusMenu *menu, void *page);

typedef struct PageHandlers {
    PageFunc open;
    PageFunc update;
    PageFunc draw;
    PageFunc close;
    void *page;
} PageHandlers;

typedef struct StatusPanel {
    u8 pad_000[0x148];
    u8 tileTable[0x168 - 0x148];
    BOOL nameShown;
    BOOL listBusy;
    u8 pad_170[0x1cc - 0x170];
    u8 textLayer[0x200 - 0x1cc];
    int selectedRecord;
} StatusPanel;

struct StatusMenu {
    s8 page;
    u8 redraw;
    u8 refresh;
    u8 flags;
    u16 munnyDigits;
    u16 timeDigits;
    int heartCount;
    int playSeconds;
    u8 pad_10[4];
    int busy;
    BOOL timerActive;
    BOOL isCurrent;
    BOOL showExtra;
    BOOL wirelessMode;
    u8 pad_28[0x16f - 0x28];
    u8 dragging;
    u8 pad_170[0x220 - 0x170];
    void *rowWidget;
    u8 pad_224[0xa58 - 0x224];
    void *progressWidget;
    u8 pad_a5c[0xb40 - 0xa5c];
    void *columnWidget;
    StatusPanel panel;
    u8 pad_d48[4];
    int selection;
    PageHandlers handlers[5];
    u8 pad_db4[0xdf4 - 0xdb4];
    u8 headerLayer[0x34];
    u8 infoLayer[0x34];
    u16 titles[2][0x20];
    u16 bodies[2][0x70];
    u16 caption[0x20];
    void *recordPool;
    void *widgets;
    int captionModes[2];
    u8 pad_10ec[0x11cc - 0x10ec];
    u8 strings[0x1228 - 0x11cc];
    s64 openTick;
};

extern u16 data_020604fc;
extern u16 data_02060500;

extern u64 OS_GetTick_02003fd4(void);
extern void func_ov039_020be450(void *cells, int first, int value, void *origin);
extern int func_ov039_020bca30(void);
extern TouchState *func_ov039_020bca00(void);
extern BOOL IsStatePhaseActive_020bca60(void);
extern int func_ov039_020bc0ec(void);
extern u32 func_ov039_020bca18(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void ResetStatusPageState_020beaa0(StatusMenu *menu);
extern void ClearSharedStateFlag_020c1c50(StatusMenu *menu, u8 mask);
extern void AddStatusMenuFlags_020c1be0(StatusMenu *menu, int flags);
extern void SetEntrySlotsVisible_020b9580(void *widgets, void *widget, int visible);
extern void *FindWidgetById_020b90a4(void *root, int id);
extern void CallStateWidget_020bc14c(int a, int b, int c, int d, int e);
extern void SetScreenLayerDirty_020bc104(int layerId);
extern void CallVirtualHandlerSlot1_02001574(void *layer, int arg);
extern void FlushBufferAndRunCallback_0200153c(void *layer);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void DrawTextColored_02001668(void *layer, int x, int y, int color, int altColor, const u16 *text);
extern int func_02001908(void *layer, const u16 *text, const u16 **next);
extern void Obj_SetField14_02001490(void *layer, void *font);
extern void *func_ov039_020bc9ac(void);
extern void *func_ov039_020bc994(void);
extern u16 *func_ov027_020ba2a8(void *strings, int index);
extern int CopySourceBlock_020b9f7c(void *dst);
extern void UpdateListScroll_020c3ce0(StatusPanel *panel, BOOL refresh, u16 input);
extern void FlushDirtyTileTableRows_020b9e60(void *table);

#define REG_POWCNT (*(vu16 *)0x04000304)

void UpdateStatusMenu_020bf62c(StatusMenu *menu)
{
    PageHandlers *handlers;
    TouchState *raw;
    TouchState *touch;
    void *widget;
    const u16 *next;
    u8 block[8];

    if (menu->timerActive && menu->busy == 0 && menu->page != 4) {
        menu->playSeconds = menu->heartCount + (int)(((OS_GetTick_02003fd4() - menu->openTick) * 64) / 0x1ff6210);
        func_ov039_020be450(menu->widgets, menu->timeDigits, menu->playSeconds, NULL);
    }
    if (func_ov039_020bca30()) {
        return;
    }
    touch = NULL;
    handlers = &menu->handlers[menu->page];
    raw = func_ov039_020bca00();
    if (((REG_POWCNT & 0x8000) >> 15) == 1) {
        touch = raw;
    }
    if (menu->showExtra == 0 && !IsStatePhaseActive_020bca60() && func_ov039_020bc0ec() != 0) {
        if (menu->flags & 2) {
            if (handlers->update(menu, handlers->page) == 0) {
                if (touch != NULL && (touch->state & 3) != 0) {
                    if ((touch->state & 3) == 1 && menu->dragging == 0 && touch->x >= 0xa0 && touch->x < 0xf0
                        && touch->y >= 4 && touch->y < 0x14) {
                        int tab = (touch->x - 0xa0) / 16;

                        if (tab != menu->page) {
                            PlaySoundEffect_0204d924(0, 2);
                            handlers->close(menu, handlers->page);
                            handlers = &menu->handlers[tab];
                            menu->page = tab;
                            ResetStatusPageState_020beaa0(menu);
                            handlers->open(menu, handlers->page);
                            menu->redraw = 1;
                        } else {
                            PlaySoundEffect_0204d924(0, 4);
                        }
                    }
                } else if ((data_02060500 & 0x40a) || (touch == NULL && (func_ov039_020bca18() & 3) == 1)) {
                    ClearSharedStateFlag_020c1c50(menu, 2);
                    SetEntrySlotsVisible_020b9580(menu->widgets, menu->rowWidget, 0);
                    SetEntrySlotsVisible_020b9580(menu->widgets, menu->progressWidget, 0);
                    SetEntrySlotsVisible_020b9580(menu->widgets, menu->columnWidget, 0);
                    SetEntrySlotsVisible_020b9580(menu->widgets, FindWidgetById_020b90a4(menu->widgets, 0xe), 0);
                    PlaySoundEffect_0204d924(0, 3);
                    menu->refresh = 2;
                    if (touch == NULL && (func_ov039_020bca18() & 3) == 1) {
                        raw->state |= 1;
                    }
                } else if (data_02060500 & 0x200) {
                    PlaySoundEffect_0204d924(0, 2);
                    handlers->close(menu, handlers->page);
                    menu->page--;
                    if (menu->page < 0) {
                        menu->page = 4;
                    }
                    handlers = &menu->handlers[menu->page];
                    ResetStatusPageState_020beaa0(menu);
                    handlers->open(menu, handlers->page);
                    menu->redraw = 1;
                } else if (data_02060500 & 0x100) {
                    PlaySoundEffect_0204d924(0, 2);
                    handlers->close(menu, handlers->page);
                    menu->page++;
                    if (menu->page == 5) {
                        menu->page = 0;
                    }
                    handlers = &menu->handlers[menu->page];
                    ResetStatusPageState_020beaa0(menu);
                    handlers->open(menu, handlers->page);
                    menu->redraw = 1;
                }
            }
        } else if ((data_020604fc == 0x400 && data_02060500 == 0x400 && (touch != NULL || !(raw->state & 3)))
                   || (touch != NULL && (touch->state & 3) == 1)) {
            PlaySoundEffect_0204d924(0, 2);
            AddStatusMenuFlags_020c1be0(menu, 2);
            switch (menu->page) {
            case 1:
                widget = menu->rowWidget;
                break;
            case 2:
                widget = menu->progressWidget;
                break;
            case 3:
                widget = menu->columnWidget;
                break;
            case 4:
                widget = FindWidgetById_020b90a4(menu->widgets, 0xe);
                break;
            default:
                widget = NULL;
                break;
            }
            if (widget != NULL) {
                SetEntrySlotsVisible_020b9580(menu->widgets, widget, 1);
                menu->redraw = 1;
            }
        }
    }

    if (menu->redraw) {
        if (menu->page != 4) {
            CallStateWidget_020bc14c(0x1a, 0, 0, 0x20, 0x12);
            SetScreenLayerDirty_020bc104(0x19);
            SetScreenLayerDirty_020bc104(0x1a);
            CallVirtualHandlerSlot1_02001574(menu->headerLayer, 0);
            handlers->draw(menu, handlers->page);
            FlushBufferAndRunCallback_0200153c(menu->headerLayer);
            menu->redraw--;
        } else {
            handlers->draw(menu, handlers->page);
            menu->redraw--;
        }
    } else if (menu->page == 4 && menu->panel.nameShown) {
        handlers->update(menu, handlers->page);
    }

    if (menu->refresh) {
        int mode = (menu->flags & 2) ? 1 : 0;

        if (menu->page != 4) {
            CallVirtualHandlerSlot1_02001574(menu->infoLayer, 0);
            if (menu->showExtra == 0 || menu->wirelessMode != 0) {
                if (menu->busy == 0) {
                    DrawTextColored_02001668(menu->infoLayer, 0x60, 8, 2, 10, menu->bodies[0]);
                } else {
                    int y = 0;

                    if (menu->titles[mode][0] != 0) {
                        const u16 *title = menu->titles[mode];

                        DrawTextAnchored_020015a0(menu->infoLayer, 4, y, 10, 8, title);
                        if (mode == 0 && menu->caption[0] != 0) {
                            if (menu->captionModes[mode] == 1) {
                                DrawTextAnchored_020015a0(menu->infoLayer, func_02001908(menu->infoLayer, title, NULL) + 12,
                                                          y, 6, 8, menu->caption);
                            } else if (menu->captionModes[mode] != 0) {
                                DrawTextAnchored_020015a0(menu->infoLayer, 0xfc, y, 6, 0x20, menu->caption);
                            }
                        }
                        y += 12;
                    }
                    if (menu->captionModes[mode] == 4 && menu->page == 1 && mode != 0) {
                        DrawTextAnchored_020015a0(menu->infoLayer, 4, 0x18, 10, 8, func_ov027_020ba2a8(menu->strings, 0x23));
                    }
                    DrawTextColored_02001668(menu->infoLayer, 4, y, 2, 6, menu->bodies[mode]);
                }
            }
            FlushBufferAndRunCallback_0200153c(menu->infoLayer);
        } else {
            StatusPanel *panel = &menu->panel;

            if (mode == 0) {
                int maxWidth = 0;
                int width;
                const u16 *text;

                CallVirtualHandlerSlot1_02001574(panel->textLayer, 0);
                text = menu->bodies[mode];
                next = text;
                do {
                    width = func_02001908(panel->textLayer, next, &next);
                    if (maxWidth < width) {
                        maxWidth = width;
                    }
                } while (next != NULL);
                if (maxWidth > 0xe4) {
                    Obj_SetField14_02001490(panel->textLayer, func_ov039_020bc9ac());
                }
                DrawTextColored_02001668(panel->textLayer, 4, 0, 2, 10, text);
                Obj_SetField14_02001490(panel->textLayer, func_ov039_020bc994());
                FlushBufferAndRunCallback_0200153c(panel->textLayer);
                panel->selectedRecord = -1;
            }
        }
        menu->refresh--;
    }

    if (menu->page == 4) {
        StatusPanel *panel = &menu->panel;

        if (panel->listBusy == 0) {
            if (((REG_POWCNT & 0x8000) >> 15) == 1) {
                if (menu->flags & 2) {
                    UpdateListScroll_020c3ce0(panel, CopySourceBlock_020b9f7c(block), data_02060500);
                } else {
                    UpdateListScroll_020c3ce0(panel, 0, 0);
                }
            } else {
                UpdateListScroll_020c3ce0(panel, 0, (menu->flags & 2) ? data_02060500 : 0);
            }
            FlushDirtyTileTableRows_020b9e60(panel->tileTable);
        }
    }
}
