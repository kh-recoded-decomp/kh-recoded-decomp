#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

typedef struct PanelRect {
    s32 values[4];
} PanelRect;

typedef struct PanelPoint {
    fx32 x;
    fx32 y;
} PanelPoint;

typedef struct PanelEntry {
    u8 pad_000[8];
    PanelPoint pos;
    u8 pad_010[0x49b];
    u8 unk_4ab_0 : 5;
    u8 isSpecial : 1;
    u8 isEquipment : 1;
} PanelEntry;

typedef struct PanelFlags {
    u8 matched : 1;
    u8 moved : 1;
    u8 dropMode : 1;
} PanelFlags;

typedef struct PanelState {
    u8 pad_0000[0x4c];
    u8 animator[0x4c];
    u8 objectList[0x647c];
    u8 entryList[0x6498];
    PanelRect savedRect;
    PanelRect dragRect;
    u8 previewInfo[0xc];
    u32 previewFlags;
    u8 pad_c9dc[0xd0];
    PanelPoint basePos;
    u8 pad_cab4[4];
    PanelEntry *dropEntry;
    PanelEntry *dragEntry;
    u8 pad_cac0[0x80];
    u16 prevButtons;
    u8 pad_cb42[6];
    u32 lockMask;
    u32 touchButtons;
    u8 *itemLists[0x14];
    u8 pad_cba0[0x38c];
    u8 itemCounts[0x14];
    s16 selectedItems[0x1a];
    s16 row;
    s16 rowCount;
    s16 column;
    s16 columnCount;
    s16 itemIndex;
    s16 itemCount;
    s16 dragStartX;
    s16 dragStartY;
    s16 dragX;
    s16 dragY;
    s16 touchHeld;
    u8 pad_cf8a[4];
    s8 mode;
    s8 step;
    s8 popupState;
    s8 popupTimer;
    u8 scrollMode;
    s8 scrollDirection;
    s8 repeatTimer;
    s8 unk_cf95;
    s8 dropSlot;
    s8 touchRegion;
    PanelFlags flags;
} PanelState;

extern u16 data_02060500;
extern u16 data_020604fc;
extern PanelState *g_panelState_0206f9a0;
extern u8 data_ov014_0206f81c[][7];
extern const u8 data_ov014_0206f7fc[];

extern int CopyRecentTouchPoints_0202b618(TouchSample *table);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_01ff8830(void *dest, int value, u32 size);
extern u16 *func_ov002_02062000(void);
extern int func_ov002_020621c4(int index, int unused);
extern void func_ov002_02061d58(int a, int x, int y, int b, int c, int d, int text, int e);
extern BOOL IsGlobalBit0Set_020632ac(void);
extern BOOL IsButtonBPressed_020632c8(void);
extern int func_ov002_02066c78(u32 message, u32 category, u32 item, void *result);
extern PanelRect *func_ov002_02066fc8(void);
extern void func_ov002_02067a84(PanelEntry *entry);
extern void func_ov002_02067c10(void *list, PanelEntry *entry);
extern void func_ov002_020680a4(void *list, PanelEntry *entry);
extern void func_ov002_02068130(void *list, PanelEntry *entry, int slot, s32 *offset);
extern void func_ov002_02068248(void *list, PanelEntry *entry, int flag);
extern void func_ov002_020682c4(void *list, PanelEntry *entry, int slot, int flag);
extern void func_ov002_02068310(void *list, PanelEntry *entry, int slot, int flag);
extern void func_ov002_0206842c(void *list, PanelEntry *entry);
extern void func_ov002_02069190(void *info, u32 category, u32 item);
extern u32 func_ov002_02069504(int owner, u32 category, int index);
extern u32 func_ov002_02069690(int owner, u32 category, u32 item);
extern void func_ov002_02069df8(u32 category, u32 item, PanelPoint *pos);
extern void ChangePanelState_0206d1c0(s8 nextState);
extern void SetPanelDirection_0206e66c(BOOL forward);
extern void UpdatePanelFade_0206e6a0(void);
extern void DrawSelectedEntryInfo_0206ea4c(BOOL keepLayer);
extern void func_ov014_0206ec14(void);
extern void BuildPanelGroupEntries_0206f0a0(void);
extern BOOL func_ov014_0206f230(void);
extern s8 func_ov014_0206f42c(int x, int y);
extern void *func_ov027_020b8390(void *animator, int index);
extern void func_ov027_020b83e8(void *animator, void *element, int flag);
extern void func_ov027_020b8874(void *list, TouchSample *points);
extern void func_ov027_020b8ca8(void *list, u32 buttons);
extern void *func_ov027_020b90a4(void *list, int index);
extern void func_ov027_020b91c8(void *list, void *element, s32 *value, int flag);
extern void func_ov027_020b9620(void *list, void *element);
extern void func_ov027_020b96a0(void *list, void *element, u16 value);

void UpdatePanelEditInput_0206d2e8(void)
{
    TouchSample points[4];
    s16 next;
    PanelState *state;
    int diff;
    PanelState *panel;
    int x;
    s32 touching;
    void *element;
    u16 padTrigger;
    int y;
    u32 item;
    u8 *list;
    s16 tapped;
    u32 buttons;
    s32 newTouch;
    u8 sound;
    int total;
    PanelEntry *entry;
    u32 selectable;
    s16 move;
    s16 messageResult;
    BOOL offset[2];
    u16 padHeld;
    u16 category;

    padTrigger = data_02060500;
    move = 0;
    padHeld = data_020604fc;
    touching = CopyRecentTouchPoints_0202b618(points);
    newTouch = 0;
    panel = g_panelState_0206f9a0;
    if (panel->touchHeld == 0 && touching) {
        newTouch = 1;
    }
    tapped = newTouch ? touching : 0;
    panel->touchHeld = touching;
    state = g_panelState_0206f9a0;

    switch (state->mode) {
    case 0:
        if (func_ov002_02066c78(0xe, 0, 0, NULL) == 0) {
            g_panelState_0206f9a0->mode = 5;
            g_panelState_0206f9a0->step = 0;
            return;
        }
        if (0 == touching) {
            g_panelState_0206f9a0->mode = 1;
        }
        break;
    case 1:
        buttons = *func_ov002_02062000();
        func_ov027_020b8ca8(g_panelState_0206f9a0->objectList, buttons);
        func_ov027_020b8ca8(g_panelState_0206f9a0->entryList, buttons);
        if (touching != 0) {
            func_ov027_020b8874(g_panelState_0206f9a0->entryList, points);
        }
        if (buttons == 0) {
            x = points[0].x;
            y = points[0].y;
            if (touching) {
                if (g_panelState_0206f9a0->touchButtons) {
                    if (tapped || (g_panelState_0206f9a0->touchButtons == g_panelState_0206f9a0->prevButtons &&
                                        0 == g_panelState_0206f9a0->touchRegion)) {
                        buttons = g_panelState_0206f9a0->touchButtons;
                    }
                } else if (y >= 0xb0) {
                    if (x < 0x18) {
                        g_panelState_0206f9a0->touchButtons = 0x200;
                    } else if (x >= 0xe8) {
                        g_panelState_0206f9a0->touchButtons = 0x100;
                    }
                    if (tapped || (g_panelState_0206f9a0->touchButtons == g_panelState_0206f9a0->prevButtons &&
                                        g_panelState_0206f9a0->touchRegion == 0)) {
                        buttons = g_panelState_0206f9a0->touchButtons;
                    }
                }
                if (g_panelState_0206f9a0->touchRegion < 0) {
                    if (x >= 0x18 && 0x6a > x && y >= 0x2a && 0x72 > y) {
                        g_panelState_0206f9a0->touchRegion = 1;
                    } else if (x >= 0x82 && x < 0xf2 && y >= 0x20 && 0xa0 > y) {
                        g_panelState_0206f9a0->touchRegion = 2;
                    } else {
                        g_panelState_0206f9a0->touchRegion = 0;
                    }
                }
                diff = g_panelState_0206f9a0->prevButtons ^ buttons;
                padHeld = buttons;
                g_panelState_0206f9a0->prevButtons = padHeld;
                padTrigger = diff;
                if (diff) {
                    g_panelState_0206f9a0->repeatTimer = 14;
                } else if (buttons) {
                    g_panelState_0206f9a0->repeatTimer--;
                    if (g_panelState_0206f9a0->repeatTimer > 0) {
                        buttons = diff;
                    } else {
                        g_panelState_0206f9a0->repeatTimer = 3;
                    }
                }
            } else {
                g_panelState_0206f9a0->prevButtons = 0;
                g_panelState_0206f9a0->touchRegion = -1;
            }
        } else {
            g_panelState_0206f9a0->prevButtons = 0;
            g_panelState_0206f9a0->touchRegion = -1;
        }
        if (g_panelState_0206f9a0->lockMask) {
            buttons = 0;
            if ((padHeld & g_panelState_0206f9a0->lockMask) == 0) {
                g_panelState_0206f9a0->lockMask = 0;
            }
        }
        if (IsButtonBPressed_020632c8() || ((buttons & 2) && tapped)) {
            PlaySoundEffect_0204d924(2, 4);
            ChangePanelState_0206d1c0(2);
            return;
        }
        if (touching && 0 == buttons) {
            x = points[0].x;
            y = points[0].y;
            if (g_panelState_0206f9a0->itemCount) {
                category = data_ov014_0206f81c[g_panelState_0206f9a0->row][g_panelState_0206f9a0->column];
                selectable = TRUE;
                item = g_panelState_0206f9a0->itemLists[category][g_panelState_0206f9a0->itemIndex];
                if (category <= 2 && item == func_ov002_02069504(0, category, 0)) {
                    selectable = FALSE;
                }
                if (selectable && 1 == g_panelState_0206f9a0->touchRegion && x >= 0x30 && 0x54 > x &&
                    y >= 0x3c && y < 0x60) {
                    g_panelState_0206f9a0->dragRect = g_panelState_0206f9a0->savedRect;
                    g_panelState_0206f9a0->dragStartX = x;
                    g_panelState_0206f9a0->dragStartY = y;
                    g_panelState_0206f9a0->dragX = x;
                    g_panelState_0206f9a0->dragY = y;
                    g_panelState_0206f9a0->flags.matched = (item == func_ov002_02069690(0, category, item));
                    g_panelState_0206f9a0->unk_cf95 = -5;
                    g_panelState_0206f9a0->mode = 4;
                    g_panelState_0206f9a0->step = 0;
                    break;
                }
                if (g_panelState_0206f9a0->touchRegion == 2) {
                    g_panelState_0206f9a0->dropSlot = func_ov014_0206f42c(x, y);
                    if (g_panelState_0206f9a0->dropSlot >= 0) {
                        move = 1;
                        g_panelState_0206f9a0->flags.dropMode = func_ov014_0206f230();
                        if (g_panelState_0206f9a0->dropSlot >= 3) {
                            func_ov002_02068310(g_panelState_0206f9a0->entryList, g_panelState_0206f9a0->dropEntry,
                                                g_panelState_0206f9a0->dropSlot, 1);
                            g_panelState_0206f9a0->dragStartX = x;
                            g_panelState_0206f9a0->dragStartY = y;
                            g_panelState_0206f9a0->dragX = x;
                            g_panelState_0206f9a0->dragY = y;
                        }
                        g_panelState_0206f9a0->mode = g_panelState_0206f9a0->flags.dropMode ? 7 : 6;
                        g_panelState_0206f9a0->step = 0;
                        break;
                    }
                }
            }
        }
        if (IsGlobalBit0Set_020632ac()) {
            if (g_panelState_0206f9a0->itemCount == 0) {
                break;
            }
            category = data_ov014_0206f81c[g_panelState_0206f9a0->row][g_panelState_0206f9a0->column];
            item = g_panelState_0206f9a0->itemLists[category][g_panelState_0206f9a0->itemIndex];
            if (category <= 2 && item == func_ov002_02069504(0, category, 0)) {
                PlaySoundEffect_0204d924(2, 5);
                break;
            }
            g_panelState_0206f9a0->mode = 3;
            g_panelState_0206f9a0->step = 0;
            g_panelState_0206f9a0->flags.matched = 1;
            break;
        }
        if (buttons & 0x300) {
            move = (buttons & 0x200) ? -1 : 1;
            next = move + g_panelState_0206f9a0->row;
            if (0 > next) {
                next = g_panelState_0206f9a0->rowCount - 1;
            } else if (next >= g_panelState_0206f9a0->rowCount) {
                next = 0;
            }
            g_panelState_0206f9a0->row = next;
            g_panelState_0206f9a0->column = 0;
            g_panelState_0206f9a0->columnCount = data_ov014_0206f7fc[next];
            category = data_ov014_0206f81c[g_panelState_0206f9a0->row][g_panelState_0206f9a0->column];
            g_panelState_0206f9a0->itemCount = g_panelState_0206f9a0->itemCounts[category];
            BuildPanelGroupEntries_0206f0a0();
            g_panelState_0206f9a0->itemIndex = g_panelState_0206f9a0->selectedItems[category];
            if ((0 > move && 0 == next) || (move > 0 && next == g_panelState_0206f9a0->rowCount - 1)) {
                g_panelState_0206f9a0->lockMask |= 0x300;
            }
            state = g_panelState_0206f9a0;
            element = func_ov027_020b90a4(state->objectList, 2);
            offset[0] = 0x30000 * next;
            func_ov027_020b91c8(state->objectList, element, offset, 4);
            func_ov027_020b96a0(state->objectList, func_ov027_020b90a4(state->objectList, 3), next);
            PlaySoundEffect_0204d924(2, 3);
            break;
        }
        if (buttons & 0xc0) {
            move = (buttons & 0x40) ? -1 : 1;
            next = g_panelState_0206f9a0->column + move;
            if (next < 0) {
                next = g_panelState_0206f9a0->columnCount - 1;
            } else if (next >= g_panelState_0206f9a0->columnCount) {
                next = 0;
            }
            g_panelState_0206f9a0->column = next;
            category = data_ov014_0206f81c[g_panelState_0206f9a0->row][g_panelState_0206f9a0->column];
            g_panelState_0206f9a0->itemCount = g_panelState_0206f9a0->itemCounts[category];
            BuildPanelGroupEntries_0206f0a0();
            g_panelState_0206f9a0->itemIndex = g_panelState_0206f9a0->selectedItems[category];
            if ((0 > move && 0 == next) || (move > 0 && next == g_panelState_0206f9a0->columnCount - 1)) {
                g_panelState_0206f9a0->lockMask |= 0xc0;
            }
            PlaySoundEffect_0204d924(2, 0);
            break;
        }
        if (buttons & 0x30) {
            total = g_panelState_0206f9a0->itemCount;
            if (total < 2) {
                break;
            }
            move = (buttons & 0x20) ? -1 : 1;
            next = move + g_panelState_0206f9a0->itemIndex;
            if (0 > next) {
                next = total - 1;
            } else if (next >= total) {
                next = 0;
            }
            g_panelState_0206f9a0->itemIndex = next;
            g_panelState_0206f9a0->selectedItems[data_ov014_0206f81c[g_panelState_0206f9a0->row][g_panelState_0206f9a0->column]] = next;
            if ((move < 0 && next == 0) || (move > 0 && next == g_panelState_0206f9a0->itemCount - 1)) {
                g_panelState_0206f9a0->lockMask |= 0x30;
            }
            PlaySoundEffect_0204d924(2, 0);
        }
        break;
    case 2:
    refresh:
        {
            panel = g_panelState_0206f9a0;
            list = panel->entryList;
            entry = panel->dragEntry;
            switch (panel->step) {
            case 0:
                if (0 == state->scrollDirection) {
                    func_ov002_0206842c(list, entry);
                    func_01ff8830(g_panelState_0206f9a0->previewInfo, 0, 0x10);
                    g_panelState_0206f9a0->previewFlags |= 0x40000000;
                    g_panelState_0206f9a0->step++;
                }
                break;
            case 1:
                if (state->itemCount) {
                    category = data_ov014_0206f81c[panel->row][panel->column];
                    item = panel->itemLists[category][panel->itemIndex];
                    func_ov002_02069190(panel->previewInfo, category, item);
                    func_ov002_02067a84(entry);
                    entry->isEquipment = (category >= 1 && 6 > category);
                    entry->isSpecial = (category == 0x12);
                    func_ov002_02069df8(category, item, &entry->pos);
                    g_panelState_0206f9a0->basePos = entry->pos;
                } else {
                    func_ov002_02067a84(entry);
                }
                func_ov002_02067c10(list, entry);
                if (g_panelState_0206f9a0->flags.moved) {
                    SetPanelDirection_0206e66c(TRUE);
                }
                if (g_panelState_0206f9a0->mode == 7) {
                    g_panelState_0206f9a0->mode = 6;
                } else {
                    g_panelState_0206f9a0->mode = 1;
                }
                break;
            }
        }
        break;
    case 3:
        list = state->entryList;
        entry = state->dropEntry;
        switch (state->step) {
        case 0:
            if (state->popupState != 1) {
                PlaySoundEffect_0204d924(2, 6);
            }
            g_panelState_0206f9a0->popupState = 1;
            if (g_panelState_0206f9a0->popupTimer < 0x12) {
                break;
            }
            g_panelState_0206f9a0->popupState = 0;
            g_panelState_0206f9a0->step++;
            break;
        case 1:
            func_ov002_0206842c(list, entry);
            g_panelState_0206f9a0->step++;
            break;
        case 2:
            category = data_ov014_0206f81c[state->row][state->column];
            item = state->itemLists[category][state->itemIndex];
            if (item == func_ov002_02069690(0, category, item)) {
                func_ov002_02066c78(0x80000019, category, item, &messageResult);
            } else {
                func_ov002_02066c78(0x80000011, category, item, &messageResult);
            }
            panel = g_panelState_0206f9a0;
            panel->savedRect = *func_ov002_02066fc8();
            panel->dragRect = panel->savedRect;
            func_ov002_02067a84(entry);
            func_ov002_02067c10(list, entry);
            g_panelState_0206f9a0->step++;
            break;
        case 3:
            state->popupState = 2;
            if (g_panelState_0206f9a0->popupTimer > 1) {
                break;
            }
            g_panelState_0206f9a0->popupState = 0;
            g_panelState_0206f9a0->step++;
            break;
        case 4:
            func_ov002_02068248(list, state->dragEntry, 1);
            if (!g_panelState_0206f9a0->flags.matched) {
                SetPanelDirection_0206e66c(TRUE);
            }
            DrawSelectedEntryInfo_0206ea4c(0);
            g_panelState_0206f9a0->mode = 1;
            break;
        }
        break;
    case 4:
        list = state->entryList;
        entry = state->dragEntry;
        if (touching) {
            y = points[0].y;
            x = points[0].x;
            if (x < 0x21) {
                x = 0x21;
            } else if (x > 0xd6) {
                x = 0xd6;
            }
            if (0x30 > y) {
                y = 0x30;
            } else if (0x6c < y) {
                y = 0x6c;
            }
            state->dragX = x;
            g_panelState_0206f9a0->dragY = y;
            x -= g_panelState_0206f9a0->dragStartX;
            y -= g_panelState_0206f9a0->dragStartY;
            entry->pos.x = g_panelState_0206f9a0->basePos.x + (x << 12);
            entry->pos.y = g_panelState_0206f9a0->basePos.y + (y << 12);
        } else {
            if (state->dragX >= 0x7e) {
                if (!state->flags.matched) {
                    func_ov002_02068248(list, entry, 0);
                }
                g_panelState_0206f9a0->mode = 3;
                g_panelState_0206f9a0->step = 0;
            } else {
                state->mode = 1;
            }
            entry->pos.x = g_panelState_0206f9a0->basePos.x;
            entry->pos.y = g_panelState_0206f9a0->basePos.y;
        }
        func_ov002_020680a4(list, entry);
        break;
    case 6:
    case 7:
        list = state->entryList;
        entry = state->dropEntry;
        if (state->dropSlot >= 3) {
            if (touching) {
                x = points[0].x;
                y = points[0].y;
                if (x < 0x78) {
                    x = 0x78;
                } else if (x > 0xfc) {
                    x = 0xfc;
                }
                if (0x16 > y) {
                    y = 0x16;
                } else if (y > 0xaa) {
                    y = 0xaa;
                }
                state->dragX = x;
                g_panelState_0206f9a0->dragY = y;
                x -= g_panelState_0206f9a0->dragStartX;
                y -= g_panelState_0206f9a0->dragStartY;
                offset[0] = x << 12;
                offset[1] = y << 12;
            } else if (6 == state->mode) {
                if (state->dragX < 0x7e || state->dragX >= 0xf6 || state->dragY < 0x1c || state->dragY >= 0xa4) {
                    func_ov002_020682c4(list, entry, state->dropSlot, 0);
                    g_panelState_0206f9a0->flags.matched = 1;
                    g_panelState_0206f9a0->mode = 3;
                    g_panelState_0206f9a0->step = 0;
                } else {
                    state->mode = 1;
                }
                *(volatile BOOL *)&offset[0] = 0;
                *(volatile BOOL *)&offset[1] = 0;
                func_ov002_02068310(list, entry, (*(PanelState *volatile *)&g_panelState_0206f9a0)->dropSlot, 0);
            }
            func_ov002_02068130(list, entry, g_panelState_0206f9a0->dropSlot, offset);
        } else if (touching == 0 && state->mode == 6) {
            state->mode = 1;
            g_panelState_0206f9a0->step = 0;
        }
        state = g_panelState_0206f9a0;
        if (state->mode == 7) {
            goto refresh;
        }
        break;
    case 5:
        switch (state->step) {
        case 0:
            func_ov027_020b83e8(state->animator, func_ov027_020b8390(state->animator, 0), 0);
            func_ov027_020b83e8(state->animator, func_ov027_020b8390(state->animator, 1), 0);
            g_panelState_0206f9a0->popupState = 3;
            func_ov002_02061d58(1, 0x80, 0x34, 2, 6, 10, func_ov002_020621c4(0x6d, 0), 0);
            PlaySoundEffect_0204d924(2, 3);
            g_panelState_0206f9a0->step++;
            break;
        case 1:
            if (!IsGlobalBit0Set_020632ac() && !IsButtonBPressed_020632c8() && (touching == 0 || tapped == 0)) {
                break;
            }
            sound = 1;
            g_panelState_0206f9a0->popupState = 4;
            func_ov002_02066c78(0x80000013, 1, 0, NULL);
            DrawSelectedEntryInfo_0206ea4c(0);
            if (IsButtonBPressed_020632c8()) {
                sound = 2;
            }
            PlaySoundEffect_0204d924(2, sound);
            g_panelState_0206f9a0->step++;
            break;
        case 2:
            func_ov027_020b83e8(state->animator, func_ov027_020b8390(state->animator, 0), 1);
            func_ov027_020b83e8(state->animator, func_ov027_020b8390(state->animator, 1), 1);
            list = g_panelState_0206f9a0->entryList;
            func_ov027_020b9620(list, func_ov027_020b90a4(list, 1));
            func_ov027_020b9620(list, func_ov027_020b90a4(list, 5));
            func_ov027_020b9620(list, func_ov027_020b90a4(list, 3));
            func_ov027_020b9620(list, func_ov027_020b90a4(list, 4));
            func_ov027_020b9620(list, func_ov027_020b90a4(list, 6));
            g_panelState_0206f9a0->step++;
        case 3:
            if (touching == 0) {
                g_panelState_0206f9a0->mode = 1;
            }
            break;
        }
        break;
    }

    if (move) {
        func_ov014_0206ec14();
        DrawSelectedEntryInfo_0206ea4c(0);
        if (padTrigger & 0x3f0) {
            g_panelState_0206f9a0->flags.moved = 1;
            SetPanelDirection_0206e66c(FALSE);
        } else {
            g_panelState_0206f9a0->flags.moved = 0;
            g_panelState_0206f9a0->scrollDirection = 1;
            g_panelState_0206f9a0->scrollMode = 1;
        }
        if (g_panelState_0206f9a0->mode < 6) {
            g_panelState_0206f9a0->unk_cf95 = -5;
        }
        g_panelState_0206f9a0->dragRect = g_panelState_0206f9a0->savedRect;
        func_ov002_02068248(g_panelState_0206f9a0->entryList, g_panelState_0206f9a0->dropEntry, 1);
        if (g_panelState_0206f9a0->mode < 6) {
            g_panelState_0206f9a0->mode = 2;
        }
        g_panelState_0206f9a0->step = 0;
    }
    UpdatePanelFade_0206e6a0();
    g_panelState_0206f9a0->touchButtons = 0;
}
