#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

#define REG_BG1CNT (*(volatile u16 *)0x0400000a)

typedef enum { BG_SCREEN_SIZE_256x256 } BgScreenSize;
typedef enum { BG_COLOR_MODE_16, BG_COLOR_MODE_256 } BgColorMode;
typedef enum { BG_SCREEN_BASE_0000 } BgScreenBase;
typedef enum { BG_CHAR_BASE_00000, BG_CHAR_BASE_14000 = 5 } BgCharBase;
typedef enum { BG_EXT_PLTT_01 } BgExtPltt;

typedef struct GridPos {
    s16 x;
    s16 y;
} __attribute__((aligned(4))) GridPos;

typedef struct CellExtent {
    u8 width;
    u8 height;
    u8 pad_02[2];
} CellExtent;

typedef struct MatrixNode {
    u16 id;
    u8 kind;
    s8 linkIndex;
    s16 slot;
    u16 groupIndex;
    u8 placed;
    u8 pad_09[0x14 - 9];
} MatrixNode;

typedef struct GridDims {
    u8 cols;
    u8 rows;
} GridDims;

typedef struct Grid {
    u8 pad_0000[4];
    u16 levelNodes[(0x18 - 4) / 2];
    MatrixNode *links[(0x98 - 0x18) / 4];
    GridDims *dims;
    MatrixNode *cells[(0x2528 - 0x9c) / 4];
    u8 groupOf[0x2be8 - 0x2528];
    u8 unlockLevel[1];
} Grid;

typedef struct SlotRecord {
    int id;
    u8 pad_04[0x20 - 4];
    int pairIndex;
} SlotRecord;

typedef struct SlotGroup {
    u8 pad_00[2];
    u16 count;
    u8 pad_04[4];
    SlotRecord *record;
} SlotGroup;

typedef struct PairEntry {
    u8 pad_00[0x40];
    const u16 *shortText;
    const u16 *longText;
} PairEntry;

typedef struct PendingEvent {
    u8 pad_00;
    u8 messageId;
    s8 position;
    s8 offsetY;
    s16 x;
    s16 y;
    s16 widgetX;
    s16 widgetY;
} PendingEvent;

typedef struct TouchState {
    s16 x;
    s16 y;
    GridPos start;
    u16 flags;
} TouchState;

typedef struct Widget {
    u8 pad_00[0x14];
    int model;
} Widget;

typedef struct TweenFlags {
    u32 started : 1;
    u32 paused : 1;
    u32 finished : 1;
    u32 reserved : 29;
} TweenFlags;

typedef struct Tween {
    u8 pad_00[0x18];
    TweenFlags flags;
    u8 pad_1c[8];
} Tween;

typedef struct Dialog {
    s32 state;
    s32 mode;
} Dialog;

typedef struct MenuFlags {
    s32 unused : 1;
    s32 linkMode : 1;
    s32 rest : 30;
} MenuFlags;

typedef struct MatrixMenu {
    u8 pad_00000[7];
    u8 listDirty;
    u8 pad_00008[4];
    BOOL dragging;
    u8 pad_00010[4];
    int headerState;
    u8 pad_00018[0x28 - 0x18];
    GridPos cursorCell;
    BOOL busy;
    s16 focusX;
    s16 focusY;
    fx32 scrollX;
    fx32 scrollY;
    u8 pad_0003c[4];
    s16 bgOffset;
    u8 pad_00042[0x4c - 0x42];
    GridPos dragOrigin;
    s32 velocityX;
    s32 velocityY;
    u8 pad_00058[0x60 - 0x58];
    BOOL scrollChanged;
    BOOL dragMoved;
    BOOL touchHeld;
    u8 pad_0006c[4];
    BOOL overview;
    BOOL scrolling;
    u8 pad_00078[4];
    BOOL linkLocked;
    BOOL field_80;
    u8 panel[0x87c - 0x84];
    SlotGroup slotGroups[(0x3c9c - 0x87c) / 0xc];
    SlotGroup *slotPages[(0x4e08 - 0x3c9c) / 4];
    u8 pad_04e08[2];
    s16 slotPageIndex;
    u8 pad_04e0c[0x4ee0 - 0x4e0c];
    u8 pageTable[0x8020 - 0x4ee0];
    Dialog dialog;
    u8 pad_08028[0x11c58 - 0x8028];
    MenuFlags flags;
    u8 pad_11c5c[0x11f40 - 0x11c5c];
    int touchMode;
    u8 pad_11f44[0x11fac - 0x11f44];
    void *currentPage;
    SlotGroup *shownSlot;
    u8 pad_11fb4[0x12dc0 - 0x11fb4];
    TouchState *touch;
    u16 menuButton;
    u8 pad_12dc6[2];
    BOOL menuOpen;
    BOOL menuPressed;
    Grid *layout;
    MatrixNode *current;
    u8 visited[0x131a4 - 0x12dd8];
    int slotLayout;
    u8 pad_131a8[0x138ec - 0x131a8];
    int slotModel;
    u8 pad_138f0[0x13e64 - 0x138f0];
    u16 noticeFlags;
    s16 unlockedGroup;
    MatrixNode *noticeNode;
    u8 pad_13e6c[4];
    MatrixNode *jumpNode;
    u8 pad_13e74[0x13e7c - 0x13e74];
    u8 overviewChoice;
    u8 pad_13e7d[0x13ee0 - 0x13e7d];
    u8 history[0x174f4 - 0x13ee0];
    int introState;
    int linkState;
    Tween introTween;
    int pendingStep;
    PendingEvent *pendingEvent;
    BOOL settingsOpened;
    u8 linkMode;
} MatrixMenu;

typedef struct SaveData {
    u8 pad_0000[0x2c5c];
    int unlockBits[1];
    u16 groupBits;
    u8 pad_2c62[0x2c67 - 0x2c62];
    u8 level;
    u8 pad_2c68[0x2c6d - 0x2c68];
    u8 groupSlots[1];
} SaveData;

extern SaveData *data_0205fe0c;
extern u16 data_020604fc;
extern const GridPos data_ov075_020d1434[];
extern const CellExtent data_ov075_020d1454[];

extern BOOL IsStatePhaseActive_020bca60(void);
extern void SetScreenBrightness_020bc648(int brightness);
extern void SetPrimaryElementEnabled_020bc054(BOOL enabled);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern BOOL func_ov039_020bc0d4(void);
extern void func_020524e8(Tween *tween);
extern void func_02052514(Tween *tween, int mode, int from, int to, int duration);
extern void func_0205255c(Tween *tween);
extern void SampleTweenValue_0205258c(Tween *tween, s32 *value);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern u32 PropagateMatrixNodeVisit_020c5778(MatrixMenu *menu, MatrixNode *node, int dir, BOOL quiet, BOOL keepSteps);
extern BOOL HasPendingUnlocks_020c49a8(void);
extern void ShowDialogMessage_020c8ce4(void *menu, int messageId, int dialogType, int cancelable, ...);
extern void ShowDialogMessageAt_020c8d0c(void *menu, int messageId, int dialogType, int position, int cancelable, ...);
extern BOOL IsDialogTransitionDone_020cfbec(Dialog *dialog);
extern void UpdateMessageDialog_020cf558(Dialog *dialog, BOOL handleInput);
extern Widget *FindWidgetById_020b90a4(int root, int id);
extern void func_ov027_020b91c8(int root, Widget *widget, fx32 *pos, int flags);
extern void func_0204f204(int root, int model, int flags);
extern void SetEntrySlotsVisible_020b9580(int root, Widget *widget, int visible);
extern BOOL HasUnvisitedLink_020c4260(MatrixMenu *menu);
extern void func_ov075_020c5d10(MatrixMenu *menu, int slot, int recordId, int flags);
extern s32 GetDialogInputMode_020c42b4(MatrixMenu *menu);
extern int HitTestToggleButtons_020d0e9c(void *panel);
extern void ToggleMatrixOverview_020cb8f8(MatrixMenu *menu);
extern int func_ov075_020d026c(void *panel);
extern int GetNodeGroupIfUnlocked_020c6080(MatrixMenu *menu, MatrixNode *node);
extern u32 ReadGlobalPackedBits_02027348(u32 bitOffset, u32 bitCount);
extern void WriteGlobalPackedBits_02027360(u32 bitOffset, u32 bitCount, u32 value);
extern void func_ov075_020c7fa8(void *history, Grid *layout, MatrixNode *node, int id);
extern int *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern PairEntry *GetRecordSlotPair0Entry_02051ec8(s32 index);
extern void SetStatusPageAndCursor_020c2ca4(int page, int index);
extern void SetStatusHeaderText_020c1d38(const u16 *shortText, const u16 *longText);
extern int *func_01ffb2f8(int model, int index, int value);
extern void SetUnlockableElementsVisible_020d0e64(int layout, BOOL visible);
extern void *func_ov027_020ba2a8(void *table, int idx);
extern void ShowEntryHeaderMessage_020cad14(MatrixMenu *menu, MatrixNode *node);
extern int GetPackedBitMask(int *bitWords, int bitIndex);
extern GridPos FindNearestReachableNode_020c8eac(Grid *grid, GridPos pos, MatrixNode **outNode, BOOL skipCurrent);
extern BOOL ShowNextUnlockNotice_020cc9fc(MatrixMenu *menu, BOOL eventMode, BOOL queryOnly);
extern void func_ov075_020c4370(MatrixMenu *menu);
extern void func_ov075_020cbb34(MatrixMenu *menu);

static inline void SetBg1Control(BgScreenSize screenSize, BgColorMode colorMode, BgScreenBase screenBase,
                                 BgCharBase charBase, BgExtPltt bgExtPltt)
{
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                       (charBase << 2) | (bgExtPltt << 13));
}

static inline u16 AbsS16(int value)
{
    s16 sign = value >> 15;
    return (value ^ sign) - sign;
}

static inline BOOL UpdateIntroSequence(MatrixMenu *menu)
{
    SaveData **save = &data_0205fe0c;
    if (menu->introState < 0) {
        return FALSE;
    }
    switch (menu->introState) {
    case 0:
        if (!IsStatePhaseActive_020bca60()) {
            GridPos start = data_ov075_020d1434[(*save)->level];
            menu->introState = 1;
            menu->focusX = start.x;
            menu->focusY = start.y;
        }
        break;
    case 1:
        if (!menu->busy) {
            func_020524e8(&menu->introTween);
            func_02052514(&menu->introTween, 0, 0, 0x10000, 300);
            func_0205255c(&menu->introTween);
            menu->introState = 2;
            PlaySoundEffect_0204d924(0, 0x2f);
        }
        break;
    case 2: {
        s32 brightness;
        SampleTweenValue_0205258c(&menu->introTween, &brightness);
        SetScreenBrightness_020bc648(brightness / FX32_ONE);
        if (menu->introTween.flags.finished) {
            func_02052514(&menu->introTween, 0, 0x10000, 0, 300);
            func_0205255c(&menu->introTween);
            u8 level;
            (*save)->level++;
            level = (*save)->level;
            menu->introState = 3;
            PropagateMatrixNodeVisit_020c5778(menu, menu->layout->cells[menu->layout->levelNodes[level]], 4, TRUE, FALSE);
        }
        break;
    }
    case 3: {
        s32 brightness;
        SampleTweenValue_0205258c(&menu->introTween, &brightness);
        SetScreenBrightness_020bc648(brightness / FX32_ONE);
        if (menu->introTween.flags.finished) {
            func_02052514(&menu->introTween, 0, 0, 0x1000, 300);
            func_0205255c(&menu->introTween);
            menu->introState = 4;
        }
        break;
    }
    case 4:
        SampleTweenValue_0205258c(&menu->introTween, NULL);
        if (menu->introTween.flags.finished) {
            if (!HasPendingUnlocks_020c49a8()) {
                ShowDialogMessage_020c8ce4(menu, 0x3a, 0, 1);
                menu->introState = 5;
            } else {
                menu->introState = 0;
            }
        }
        break;
    case 5:
        UpdateMessageDialog_020cf558(&menu->dialog, IsDialogTransitionDone_020cfbec(&menu->dialog));
        if (menu->dialog.state == 4) {
            menu->introState = -1;
        }
        break;
    }
    if (menu->introState < 0) {
        SetPrimaryElementEnabled_020bc054(TRUE);
        if (menu->pendingEvent == NULL) {
            SetSecondaryElementEnabled_020bc084(TRUE);
        }
    }
    if (menu->introState >= 0) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL UpdatePendingEvent(MatrixMenu *menu)
{
    PendingEvent *event;

    if (!menu->scrolling && menu->pendingEvent == NULL) {
        return FALSE;
    }
    event = menu->pendingEvent;
    if (event != NULL) {
        switch (menu->pendingStep) {
        case 1:
            if (event->offsetY == 0) {
                menu->focusX = event->x;
                menu->focusY = event->y + 0x30;
            } else {
                MatrixNode *node = menu->jumpNode;
                int cols;
                int kind;
                int index;
                const CellExtent *extent;
                if (node == NULL) {
                    node = menu->current;
                }
                cols = menu->layout->dims->cols;
                kind = node->kind;
                if (kind < 3 || kind >= 14) {
                    index = 0;
                } else {
                    index = kind - 2;
                }
                extent = &data_ov075_020d1454[index];
                menu->focusX = extent->width / 2 + (node->id % cols) * 16;
                menu->focusY = menu->pendingEvent->offsetY + (extent->height / 2 + (node->id / cols) * 16 + 0x38);
                menu->jumpNode = NULL;
            }
            menu->pendingStep++;
            break;
        case 2:
            if (!menu->busy) {
                menu->field_80 = FALSE;
                if (event->widgetX >= 0) {
                    Widget *widget = FindWidgetById_020b90a4(menu->slotLayout, 0x2a);
                    fx32 pos[2];
                    pos[0] = menu->pendingEvent->widgetX << FX32_SHIFT;
                    pos[1] = menu->pendingEvent->widgetY << FX32_SHIFT;
                    func_ov027_020b91c8(menu->slotLayout, widget, pos, 0);
                    func_0204f204(menu->slotLayout, widget->model, 0);
                    SetEntrySlotsVisible_020b9580(menu->slotLayout, widget, 1);
                }
                ShowDialogMessageAt_020c8d0c(menu, menu->pendingEvent->messageId, 0, menu->pendingEvent->position, 1);
                menu->pendingStep++;
                menu->pendingEvent = NULL;
            }
            break;
        }
    } else {
        UpdateMessageDialog_020cf558(&menu->dialog, IsDialogTransitionDone_020cfbec(&menu->dialog));
    }
    if (menu->dialog.mode == 2 && menu->flags.linkMode != menu->linkMode) {
        u8 linked;
        menu->linkMode = menu->flags.linkMode;
        linked = menu->linkMode;
        if (menu->linkState == 1) {
            int flags = 0;
            if (linked && HasUnvisitedLink_020c4260(menu)) {
                flags = 10;
            }
            func_ov075_020c5d10(menu, -1, -1, flags);
        }
    }
    return TRUE;
}

static inline BOOL IsInputLocked(void)
{
    if (func_ov039_020bc0d4()) {
        return FALSE;
    }
    return TRUE;
}

static inline BOOL IsGroupUnlocked(MatrixNode *node)
{
    if (node->kind == 1 && (data_0205fe0c->groupBits & (1 << node->groupIndex))) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL IsEmptyLink(const MatrixMenu *menu)
{
    BOOL empty = FALSE;
    MatrixNode *node = menu->current;
    if (!(node->kind != 1 || node->slot >= 0)) {
        empty = TRUE;
    }
    return empty;
}

static inline BOOL CanFillLink(const MatrixMenu *menu)
{
    BOOL fillable = FALSE;
    if (IsEmptyLink(menu) && !menu->linkLocked) {
        fillable = TRUE;
    }
    return fillable;
}

static inline BOOL IsLastLinkInGroup(const MatrixMenu *menu)
{
    BOOL last = FALSE;
    if (CanFillLink(menu) && menu->visited[menu->current->groupIndex] == 1) {
        last = TRUE;
    }
    return last;
}

static inline void *GetPage(MatrixMenu *menu, int id)
{
    if (id >= 0) {
        return func_ov027_020ba2a8(menu->pageTable, id);
    }
    return NULL;
}

static inline int GetNodeIndex(Grid *grid, MatrixNode *node)
{
    if (node >= grid->links[0]) {
        return node - grid->links[0];
    }
    return -1;
}

BOOL UpdateMatrixMenu_020c707c(MatrixMenu *menu, int slot, int noticeFlags, BOOL commit)
{
    u16 touchFlags;
    BOOL snap;
    int prevSlot;
    int page;
    int pageIndex;
    BOOL hadSlot;
    BOOL removed;
    u8 groupId;
    BOOL result;
    u16 id;
    int mode;

    if (UpdateIntroSequence(menu) || UpdatePendingEvent(menu) || IsInputLocked()) {
        return FALSE;
    }
    if (GetDialogInputMode_020c42b4(menu) == 2) {
        int choice = HitTestToggleButtons_020d0e9c(menu->panel);
        if (choice >= 0) {
            if (menu->overviewChoice == choice) {
                ToggleMatrixOverview_020cb8f8(menu);
            } else {
                menu->overviewChoice = choice;
                PlaySoundEffect_0204d924(1, 0);
            }
        }
    } else if (GetDialogInputMode_020c42b4(menu) == 1) {
        if ((menu->touch->flags & 3) == 1) {
            ToggleMatrixOverview_020cb8f8(menu);
        }
    } else {
        mode = func_ov075_020d026c(menu->panel);
        menu->touchMode = mode;
        result = (menu->touch->flags & 1) && !menu->touchHeld;

        if (mode == 2) {
            PairEntry *entry;
            SlotGroup *group;
            MatrixNode *node;

            node = menu->current;
            group = menu->slotPages[menu->slotPageIndex];
            groupId = menu->layout->groupOf[node->id];
            commit = FALSE;
            removed = FALSE;
            hadSlot = FALSE;
            pageIndex = -1;
            page = 5;
            prevSlot = -1;

            menu->unlockedGroup = -1;
            if (node->slot < 0) {
                node->placed = FALSE;
                removed = TRUE;
                noticeFlags = 0;
                if (node->kind == 1) {
                    menu->visited[node->groupIndex]--;
                    if (menu->visited[node->groupIndex] == 0) {
                        menu->unlockedGroup = GetNodeGroupIfUnlocked_020c6080(menu, node);
                        noticeFlags = menu->unlockedGroup >= 0 ? 20 : 0;
                    }
                }
                commit = TRUE;
            } else {
                SlotGroup *oldGroup = &menu->slotGroups[node->slot];
                oldGroup->count--;
                prevSlot = node->slot;
                noticeFlags = IsGroupUnlocked(node);
                hadSlot = TRUE;
            }
            node->slot = group->record->id;
            group->count++;
            if (commit) {
                u16 count = ReadGlobalPackedBits_02027348(0xbf0, 8);
                WriteGlobalPackedBits_02027360(0xbf0, 8, count + 1);
                func_ov075_020c7fa8(menu->history, menu->layout, node, node->id);
            }
            func_ov075_020c5d10(menu, prevSlot, group->record->id, noticeFlags);
            menu->shownSlot = NULL;
            if (group->record->pairIndex != -1) {
                pageIndex = *GetRecordSlotPair1Entry_02051ef4(group->record->pairIndex);
                page = 2;
            }
            if (page < 5) {
                SetStatusPageAndCursor_020c2ca4(page, pageIndex);
            }
            data_0205fe0c->groupSlots[groupId] = node->slot - 0x90;
            entry = GetRecordSlotPair0Entry_02051ec8(node->slot);
            SetStatusHeaderText_020c1d38(entry->shortText, entry->longText);
            if (removed) {
                menu->noticeFlags |= 1;
                menu->noticeNode = node;
                func_01ffb2f8(menu->slotModel, 2, 0);
                func_01ffb2f8(menu->slotModel, 4, 0);
                func_01ffb2f8(menu->slotModel, 0, 0);
                SetSecondaryElementEnabled_020bc084(FALSE);
                SetUnlockableElementsVisible_020d0e64(menu->slotLayout, FALSE);
            } else {
                PlaySoundEffect_0204d924(1, 5);
            }
            menu->currentPage = GetPage(menu, hadSlot ? 0x58 : -1);
            menu->listDirty = TRUE;
            menu->shownSlot = NULL;
        }

        if (mode == 0) {
            TouchState *touch = menu->touch;
            touchFlags = touch->flags;

            menu->settingsOpened = FALSE;
            if (!menu->touchHeld && !menu->overview) {
                s16 startX = touch->start.x;
                s16 startY = touch->start.y;
                int dx = (s16)(touch->x - startX);
                int dy = (s16)(touch->y - startY);
                s16 distX = AbsS16((s16)(menu->dragOrigin.x - startX));
                s16 distY = AbsS16((s16)(menu->dragOrigin.y - startY));
                int phase = touchFlags & 3;

                if (phase == 1) {
                    menu->dragOrigin = touch->start;
                    menu->dragMoved = FALSE;
                    menu->dragging = TRUE;
                    SetSecondaryElementEnabled_020bc084(FALSE);
                } else if (menu->dragging) {
                    if (phase == 2) {
                        if (!menu->dragMoved && AbsS16(dx) < 4 && AbsS16(dy) < 4) {
                            MatrixNode *node;
                            GridPos cell;
                            cell.x = (menu->focusX + startX - 0x80) >> 4;
                            cell.y = (menu->focusY + startY - 0x58) >> 4;
                            SetSecondaryElementEnabled_020bc084(TRUE);
                            if (!(*(u32 *)&cell & 0x80008000)) {
                                Grid *layout = menu->layout;
                                GridDims *dims = layout->dims;
                                int cols = dims->cols;
                                if (cell.x < cols && cell.y < dims->rows &&
                                    (node = layout->cells[cell.x + cell.y * cols]) != NULL) {
                                    SaveData *save = data_0205fe0c;
                                    if (layout->unlockLevel[node->id] <= save->level &&
                                        (node->kind < 14 || node->linkIndex >= 0)) {
                                        BOOL valid = TRUE;
                                        snap = TRUE;
                                        if (node->kind == 4 || node->kind == 5) {
                                            BOOL unlocked = GetPackedBitMask(save->unlockBits, GetNodeIndex(layout, node)) ? TRUE : FALSE;
                                            valid = TRUE;
                                            if (unlocked) {
                                                valid = FALSE;
                                            }
                                        } else if (node->linkIndex >= 0) {
                                            valid = GetPackedBitMask(save->unlockBits, node->linkIndex) ? TRUE : FALSE;
                                            valid = !valid;
                                            if (valid) {
                                                node = menu->layout->links[node->linkIndex];
                                                cols = menu->layout->dims->cols;
                                                id = node->id;
                                                cell.x = id % cols;
                                                cell.y = id / cols;
                                                snap = FALSE;
                                            }
                                        }
                                        if (valid) {
                                            if (snap) {
                                                menu->cursorCell = FindNearestReachableNode_020c8eac(menu->layout, cell, &node, TRUE);
                                            } else {
                                                menu->cursorCell = cell;
                                            }
                                            menu->current = node;
                                            ShowEntryHeaderMessage_020cad14(menu, menu->current);
                                            if (!ShowNextUnlockNotice_020cc9fc(menu, TRUE, FALSE)) {
                                                func_ov075_020c4370(menu);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else if (menu->scrollChanged || (phase == 3 && distX >= 4 && distY >= 4)) {
                        menu->velocityX += dx << FX32_SHIFT;
                        menu->velocityY += dy << FX32_SHIFT;
                        menu->dragMoved = TRUE;
                        if (!menu->scrollChanged) {
                            menu->headerState = 0;
                            menu->scrollChanged = TRUE;
                            SetStatusHeaderText_020c1d38(NULL, NULL);
                        }
                    }
                    if (phase == 2) {
                        menu->dragging = FALSE;
                    }
                }
            }
            if (!(touchFlags & 1)) {
                menu->touchHeld = FALSE;
                if (!(touchFlags & 3)) {
                    switch (menu->menuButton & 3) {
                    case 1:
                        menu->menuOpen = TRUE;
                        menu->menuPressed = TRUE;
                        break;
                    case 3:
                        if (menu->menuOpen && (data_020604fc & 0xf0)) {
                            u16 keys;
                            if (menu->menuPressed) {
                                menu->menuPressed = FALSE;
                                SetUnlockableElementsVisible_020d0e64(menu->slotLayout, FALSE);
                                if (!menu->scrollChanged) {
                                    menu->headerState = 0;
                                    menu->scrollChanged = TRUE;
                                    SetStatusHeaderText_020c1d38(NULL, NULL);
                                }
                            }
                            keys = data_020604fc;
                            if (keys & 0x20) {
                                menu->scrollX -= 0xc000;
                            }
                            if (keys & 0x40) {
                                menu->scrollY -= 0xc000;
                            }
                            if (keys & 0x10) {
                                menu->scrollX += 0xc000;
                            }
                            if (keys & 0x80) {
                                menu->scrollY += 0xc000;
                            }
                        }
                        result = menu->scrollChanged;
                        break;
                    case 2:
                        if (menu->menuOpen) {
                            menu->menuOpen = FALSE;
                            if (menu->menuPressed) {
                                func_ov075_020cbb34(menu);
                            } else {
                                SetUnlockableElementsVisible_020d0e64(menu->slotLayout, TRUE);
                                data_020604fc &= 0xff0f;
                                menu->settingsOpened = TRUE;
                            }
                        }
                        break;
                    }
                }
            }
            menu->shownSlot = NULL;
        } else {
            SlotGroup *group = menu->slotPages[menu->slotPageIndex];
            menu->touchHeld = TRUE;
            if (mode != 1) {
                SetBg1Control(BG_SCREEN_SIZE_256x256, BG_COLOR_MODE_256, BG_SCREEN_BASE_0000, BG_CHAR_BASE_14000,
                              BG_EXT_PLTT_01);
                menu->bgOffset -= 5;
            }
            if (mode != 3 && menu->shownSlot != group) {
                if (mode != 2) {
                    MatrixNode *node = menu->current;
                    slot = node->slot;
                    int flags;
                    if (slot <= -1) {
                        slot = -1;
                    }
                    if (IsLastLinkInGroup(menu)) {
                        flags = 4;
                    } else {
                        flags = IsGroupUnlocked(node);
                    }
                    func_ov075_020c5d10(menu, slot, group->record->id, flags | 2);
                }
                menu->shownSlot = group;
            } else if (mode == 3) {
                func_ov075_020c5d10(menu, -1, -1, 2);
                menu->shownSlot = NULL;
                menu->currentPage = func_ov027_020ba2a8(menu->pageTable, 0x58);
                menu->listDirty = TRUE;
                ShowEntryHeaderMessage_020cad14(menu, menu->current);
            }
        }
        return result;
    }
    return FALSE;
}
