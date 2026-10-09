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

extern u64 OS_GetTick(void);
extern void func_ov039_020be470(void *cells, int first, int value, void *origin);
extern int IsStatePhase4(void);
extern TouchState *GetMenuInputState(void);
extern BOOL IsStatePhaseActive(void);
extern int GetSecondaryElementEnabled(void);
extern u32 GetEventStateWordCa48(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void ResetStatusPageState(StatusMenu *menu);
extern void ClearSharedStateFlag(StatusMenu *menu, u8 mask);
extern void AddStatusMenuFlags(StatusMenu *menu, int flags);
extern void SetEntrySlotsVisible(void *widgets, void *widget, int visible);
extern void *FindWidgetById(void *root, int id);
extern void CallStateWidget(int a, int b, int c, int d, int e);
extern void SetScreenLayerDirty(int layerId);
extern void CallVirtualHandlerSlot1(void *layer, int arg);
extern void FlushBufferAndRunCallback(void *layer);
extern void DrawTextAnchored(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void DrawTextColored(void *layer, int x, int y, int color, int altColor, const u16 *text);
extern int func_0200191c(void *layer, const u16 *text, const u16 **next);
extern void Obj_SetField14(void *layer, void *font);
extern void *GetMenuFont10s(void);
extern void *GetMenuFont10(void);
extern u16 *func_ov027_020ba2c8(void *strings, int index);
extern int func_ov027_020b9f9c(void *dst);
extern void UpdateListScroll(StatusPanel *panel, BOOL refresh, u16 input);
extern void FlushDirtyTileTableRows(void *table);

#define REG_POWCNT (*(vu16 *)0x04000304)

void UpdateStatusMenu(StatusMenu *menu)
{
    PageHandlers *handlers;
    TouchState *raw;
    TouchState *touch;
    void *widget;
    const u16 *next;
    u8 block[8];

    if (menu->timerActive && menu->busy == 0 && menu->page != 4) {
        menu->playSeconds = menu->heartCount + (int)(((OS_GetTick() - menu->openTick) * 64) / 0x1ff6210);
        func_ov039_020be470(menu->widgets, menu->timeDigits, menu->playSeconds, NULL);
    }
    if (IsStatePhase4()) {
        return;
    }
    touch = NULL;
    handlers = &menu->handlers[menu->page];
    raw = GetMenuInputState();
    if (((REG_POWCNT & 0x8000) >> 15) == 1) {
        touch = raw;
    }
    if (menu->showExtra == 0 && !IsStatePhaseActive() && GetSecondaryElementEnabled() != 0) {
        if (menu->flags & 2) {
            if (handlers->update(menu, handlers->page) == 0) {
                if (touch != NULL && (touch->state & 3) != 0) {
                    if ((touch->state & 3) == 1 && menu->dragging == 0 && touch->x >= 0xa0 && touch->x < 0xf0
                        && touch->y >= 4 && touch->y < 0x14) {
                        int tab = (touch->x - 0xa0) / 16;

                        if (tab != menu->page) {
                            PlaySoundEffect(0, 2);
                            handlers->close(menu, handlers->page);
                            handlers = &menu->handlers[tab];
                            menu->page = tab;
                            ResetStatusPageState(menu);
                            handlers->open(menu, handlers->page);
                            menu->redraw = 1;
                        } else {
                            PlaySoundEffect(0, 4);
                        }
                    }
                } else if ((data_02060500 & 0x40a) || (touch == NULL && (GetEventStateWordCa48() & 3) == 1)) {
                    ClearSharedStateFlag(menu, 2);
                    SetEntrySlotsVisible(menu->widgets, menu->rowWidget, 0);
                    SetEntrySlotsVisible(menu->widgets, menu->progressWidget, 0);
                    SetEntrySlotsVisible(menu->widgets, menu->columnWidget, 0);
                    SetEntrySlotsVisible(menu->widgets, FindWidgetById(menu->widgets, 0xe), 0);
                    PlaySoundEffect(0, 3);
                    menu->refresh = 2;
                    if (touch == NULL && (GetEventStateWordCa48() & 3) == 1) {
                        raw->state |= 1;
                    }
                } else if (data_02060500 & 0x200) {
                    PlaySoundEffect(0, 2);
                    handlers->close(menu, handlers->page);
                    menu->page--;
                    if (menu->page < 0) {
                        menu->page = 4;
                    }
                    handlers = &menu->handlers[menu->page];
                    ResetStatusPageState(menu);
                    handlers->open(menu, handlers->page);
                    menu->redraw = 1;
                } else if (data_02060500 & 0x100) {
                    PlaySoundEffect(0, 2);
                    handlers->close(menu, handlers->page);
                    menu->page++;
                    if (menu->page == 5) {
                        menu->page = 0;
                    }
                    handlers = &menu->handlers[menu->page];
                    ResetStatusPageState(menu);
                    handlers->open(menu, handlers->page);
                    menu->redraw = 1;
                }
            }
        } else if ((data_020604fc == 0x400 && data_02060500 == 0x400 && (touch != NULL || !(raw->state & 3)))
                   || (touch != NULL && (touch->state & 3) == 1)) {
            PlaySoundEffect(0, 2);
            AddStatusMenuFlags(menu, 2);
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
                widget = FindWidgetById(menu->widgets, 0xe);
                break;
            default:
                widget = NULL;
                break;
            }
            if (widget != NULL) {
                SetEntrySlotsVisible(menu->widgets, widget, 1);
                menu->redraw = 1;
            }
        }
    }

    if (menu->redraw) {
        if (menu->page != 4) {
            CallStateWidget(0x1a, 0, 0, 0x20, 0x12);
            SetScreenLayerDirty(0x19);
            SetScreenLayerDirty(0x1a);
            CallVirtualHandlerSlot1(menu->headerLayer, 0);
            handlers->draw(menu, handlers->page);
            FlushBufferAndRunCallback(menu->headerLayer);
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
            CallVirtualHandlerSlot1(menu->infoLayer, 0);
            if (menu->showExtra == 0 || menu->wirelessMode != 0) {
                if (menu->busy == 0) {
                    DrawTextColored(menu->infoLayer, 0x60, 8, 2, 10, menu->bodies[0]);
                } else {
                    int y = 0;

                    if (menu->titles[mode][0] != 0) {
                        const u16 *title = menu->titles[mode];

                        DrawTextAnchored(menu->infoLayer, 4, y, 10, 8, title);
                        if (mode == 0 && menu->caption[0] != 0) {
                            if (menu->captionModes[mode] == 1) {
                                DrawTextAnchored(menu->infoLayer, func_0200191c(menu->infoLayer, title, NULL) + 12,
                                                          y, 6, 8, menu->caption);
                            } else if (menu->captionModes[mode] != 0) {
                                DrawTextAnchored(menu->infoLayer, 0xfc, y, 6, 0x20, menu->caption);
                            }
                        }
                        y += 12;
                    }
                    if (menu->captionModes[mode] == 4 && menu->page == 1 && mode != 0) {
                        DrawTextAnchored(menu->infoLayer, 4, 0x18, 10, 8, func_ov027_020ba2c8(menu->strings, 0x23));
                    }
                    DrawTextColored(menu->infoLayer, 4, y, 2, 6, menu->bodies[mode]);
                }
            }
            FlushBufferAndRunCallback(menu->infoLayer);
        } else {
            StatusPanel *panel = &menu->panel;

            if (mode == 0) {
                int maxWidth = 0;
                int width;
                const u16 *text;

                CallVirtualHandlerSlot1(panel->textLayer, 0);
                text = menu->bodies[mode];
                next = text;
                do {
                    width = func_0200191c(panel->textLayer, next, &next);
                    if (maxWidth < width) {
                        maxWidth = width;
                    }
                } while (next != NULL);
                if (maxWidth > 0xe4) {
                    Obj_SetField14(panel->textLayer, GetMenuFont10s());
                }
                DrawTextColored(panel->textLayer, 4, 0, 2, 10, text);
                Obj_SetField14(panel->textLayer, GetMenuFont10());
                FlushBufferAndRunCallback(panel->textLayer);
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
                    UpdateListScroll(panel, func_ov027_020b9f9c(block), data_02060500);
                } else {
                    UpdateListScroll(panel, 0, 0);
                }
            } else {
                UpdateListScroll(panel, 0, (menu->flags & 2) ? data_02060500 : 0);
            }
            FlushDirtyTileTableRows(panel->tileTable);
        }
    }
}
