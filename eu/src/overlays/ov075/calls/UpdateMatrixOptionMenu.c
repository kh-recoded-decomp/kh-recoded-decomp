#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MatrixNode {
    u16 index;
    u8 type;
    s8 requiredFlag;
} MatrixNode;

typedef struct MatrixMap {
    u8 pad_00[0x98];
    u8 *columns;
} MatrixMap;

typedef struct MatrixEvent {
    u8 pad_00;
    u8 messageId;
    s8 messageArg;
    s8 offsetY;
    s16 x;
    s16 y;
    s16 widgetX;
    s16 widgetY;
} MatrixEvent;

typedef union CellOffset {
    struct {
        s16 x;
        s16 y;
    } pos;
    u32 raw;
} CellOffset;

typedef struct Dialog {
    int state;
    int mode;
    u8 pad_0008[0x9c38 - 0x8];
    s32 transitionDone : 1;
    s32 inputFlag : 1;
} Dialog;

typedef struct StatPreview {
    u32 flags;
    s16 level;
    s16 maxHp;
    s16 attack;
    s16 defense;
    s16 magic;
    s16 capacity;
    int keepCurrent;
    int reserved;
} StatPreview;

typedef struct PlayerStats {
    u8 kind;
    u8 level;
    u16 unk_2;
    u16 hp;
    u16 strength;
    u16 magic;
    u16 defense;
    u16 unk_c;
} PlayerStats;

typedef struct Widget {
    u8 pad_00[0x14];
    int cellIndex;
} Widget;

typedef struct WidgetPos {
    fx32 x;
    fx32 y;
} WidgetPos;

typedef struct PageTab {
    u8 id;
    u8 icon;
} PageTab;

typedef struct FocusOffset {
    u8 x;
    u8 y;
    u8 pad[2];
} FocusOffset;

typedef struct SaveData {
    u8 pad_0000[0x2c6c];
    u8 unlockedPages;
} SaveData;

typedef struct MatrixMenu MatrixMenu;
typedef BOOL (*OptionApplyFunc)(MatrixMenu *menu, u8 *target, BOOL apply);
typedef void (*OptionUpdateFunc)(MatrixMenu *menu);

struct MatrixMenu {
    u8 pad_00000[7];
    u8 needsRedraw;
    u8 pad_00008[0x28 - 0x8];
    s16 cursorX;
    s16 cursorY;
    int busy;
    s16 focusX;
    s16 focusY;
    fx32 viewX;
    fx32 viewY;
    u8 pad_0003c[0x74 - 0x3c];
    int scrolling;
    u8 pad_00078[0x80 - 0x78];
    int touchHeld;
    u8 pad_00084[0x4ee0 - 0x84];
    int messageBank[4];
    u8 pad_04ef0[0x8020 - 0x4ef0];
    Dialog dialog;
    u8 pad_11c5c[0x11fac - 0x8020 - sizeof(Dialog)];
    void *currentMessage;
    u8 pad_11fb0[0x12dd0 - 0x11fb0];
    MatrixMap *map;
    MatrixNode *current;
    u8 pad_12dd8[0x131a4 - 0x12dd8];
    void *layout;
    u8 pad_131a8[0x13e70 - 0x131a8];
    MatrixNode *lastNode;
    u8 pad_13e74[0x13e7d - 0x13e74];
    u8 choice;
    u8 pad_13e7e[0x13e80 - 0x13e7e];
    int noticePending;
    int noticeArmed;
    u8 pad_13e88[0x13e8c - 0x13e88];
    u8 *targets[5];
    int page;
    OptionApplyFunc onApply;
    OptionUpdateFunc onUpdate;
    u8 pad_13eac[0x13eb0 - 0x13eac];
    int repeatCount;
    u8 pad_13eb4[0x13eb8 - 0x13eb4];
    CellOffset currentOffset;
    CellOffset savedOffset;
    u8 pad_13ec0[0x174f8 - 0x13ec0];
    int mode;
    u8 pad_174fc[0x17520 - 0x174fc];
    int eventStep;
    MatrixEvent *event;
    u8 pad_17528[0x1752c - 0x17528];
    u8 lastInputFlag;
};

extern SaveData *data_0205fe0c;
extern u16 data_02060500;
extern const PageTab data_ov075_020d140a[];
extern const OptionApplyFunc gOv075StateHandlers[];
extern const OptionUpdateFunc gOv075CursorHandlers[];
extern const FocusOffset sMatrixModeLabels[];
extern const StatPreview sOv075_Empty_020d1568;

extern u32 GetPrimaryElementEnabled(void);
extern Widget *FindWidgetById(void *root, int id);
extern void func_ov027_020b91e8(void *root, Widget *widget, WidgetPos *pos, int mode);
extern void func_0204f218(void *root, int index, int value);
extern void SetEntrySlotsVisible(void *root, Widget *widget, BOOL visible);
extern MatrixNode *FindPageEntryById(MatrixMap *map, u32 id);
extern void *func_ov027_020ba2c8(int *bank, int index);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern int func_ov001_020644b0(void);
extern void ComputePlayerStats(SaveData *save, PlayerStats *out, BOOL recompute, int scaleParam);
extern void RefreshStatusMenuData(SaveData *save, StatPreview *preview);
extern void SetStatusPageAndCursor(int page, int index);
extern BOOL HasUnvisitedLink(MatrixMenu *menu);
extern void ResetDirectionRepeat(MatrixMenu *menu);
extern CellOffset GetSlotCellOffset(int code);
extern void func_ov075_020c5d30(MatrixMenu *menu, int a, int b, int c);
extern int GetOptionChangeNotice(MatrixMenu *menu);
extern void ResetMatrixDescription(MatrixMenu *menu);
extern void UpdateDirectionRepeat(MatrixMenu *menu);
extern void CommitOptionChoice(MatrixMenu *menu, BOOL confirmed);
extern void ShowDialogMessage(MatrixMenu *menu, int messageId, int dialogType, int cancelable, ...);
extern void ShowDialogMessageAt(MatrixMenu *menu, int messageId, int dialogType, int position, int cancelable, ...);
extern void ShowEntryHeaderMessage(MatrixMenu *menu, MatrixNode *entry);
extern void ShowNextUnlockNotice(MatrixMenu *menu, int a, int b);
extern void UpdateMessageDialog(Dialog *dialog, BOOL handleInput);
extern BOOL IsDialogTransitionDone(Dialog *dialog);

static inline BOOL IsMenuInactive(void)
{
    if (GetPrimaryElementEnabled()) {
        return FALSE;
    }
    return TRUE;
}

static inline void *GetBankMessage(MatrixMenu *menu, int index)
{
    return index >= 0 ? func_ov027_020ba2c8(menu->messageBank, index) : NULL;
}

static inline BOOL UpdateMenuEvent(MatrixMenu *menu)
{
    MatrixEvent *event;
    MatrixNode *node;
    int columns;
    int slot;
    const FocusOffset *offset;
    Widget *widget;
    WidgetPos pos;
    int arg;
    u8 enabled;
    int type;

    if (menu->scrolling == 0 && menu->event == NULL) {
        return FALSE;
    }
    event = menu->event;
    if (event != NULL) {
        switch (menu->eventStep) {
        case 1:
            if (event->offsetY == 0) {
                menu->focusX = event->x;
                menu->focusY = event->y + 0x30;
            } else {
                node = menu->lastNode;
                if (node == NULL) {
                    node = menu->current;
                }
                columns = *menu->map->columns;
                type = node->type;
                if (type < 3 || type >= 0xe) {
                    slot = 0;
                } else {
                    slot = type - 2;
                }
                offset = &sMatrixModeLabels[slot];
                menu->focusX = ((u32)offset->x >> 1) + (node->index % columns) * 16;
                menu->focusY = menu->event->offsetY + (((u32)offset->y >> 1) + (node->index / columns) * 16 + 0x38);
                menu->lastNode = NULL;
            }
            menu->eventStep++;
            break;
        case 2:
            if (menu->busy != 0) {
                break;
            }
            menu->touchHeld = 0;
            if (event->widgetX >= 0) {
                widget = FindWidgetById(menu->layout, 0x2a);
                pos.x = menu->event->widgetX << 12;
                pos.y = menu->event->widgetY << 12;
                func_ov027_020b91e8(menu->layout, widget, &pos, 0);
                func_0204f218(menu->layout, widget->cellIndex, 0);
                SetEntrySlotsVisible(menu->layout, widget, TRUE);
            }
            ShowDialogMessageAt(menu, menu->event->messageId, 0, menu->event->messageArg, 1);
            menu->eventStep++;
            menu->event = NULL;
            break;
        }
    } else {
        UpdateMessageDialog(&menu->dialog, IsDialogTransitionDone(&menu->dialog));
    }
    if (menu->dialog.mode == 2 && menu->dialog.inputFlag != menu->lastInputFlag) {
        menu->lastInputFlag = menu->dialog.inputFlag;
        enabled = menu->lastInputFlag;
        if (menu->mode == 1) {
            arg = 0;
            if (enabled && HasUnvisitedLink(menu)) {
                arg = 10;
            }
            func_ov075_020c5d30(menu, -1, -1, arg);
        }
    }
    return TRUE;
}

static inline BOOL OpenPage(MatrixMenu *menu, u8 index, u8 id)
{
    menu->current = FindPageEntryById(menu->map, id);
    menu->cursorX = menu->current->index % *menu->map->columns;
    menu->cursorY = menu->current->index / *menu->map->columns;
    PlaySoundEffect(1, 2);
    menu->currentMessage = GetBankMessage(menu, menu->current->type + 0x12);
    menu->needsRedraw = 1;
    menu->choice = *menu->targets[index];
    menu->onApply = gOv075StateHandlers[index];
    menu->onUpdate = gOv075CursorHandlers[index];
    menu->page = index + 1;
    menu->repeatCount = 0;
    ResetDirectionRepeat(menu);
    ShowEntryHeaderMessage(menu, menu->current);
    menu->noticePending = menu->page == 1 && menu->noticeArmed != 0 && func_ov001_020644b0() == 400;
    return TRUE;
}

static inline void ApplySlotOffset(MatrixMenu *menu, u8 code)
{
    CellOffset offset = GetSlotCellOffset(code);

    menu->savedOffset = offset;
    menu->currentOffset = offset;
}

int UpdateMatrixOptionMenu(MatrixMenu *menu)
{
    BOOL atTarget;
    u16 pad;
    u8 previous;
    BOOL applied;
    u8 *target;
    int notice;

    if (IsMenuInactive() || UpdateMenuEvent(menu)) {
        return 0;
    }
    atTarget = FALSE;
    if ((menu->focusX << 12) == menu->viewX && (menu->focusY << 12) == menu->viewY) {
        atTarget = TRUE;
    }
    pad = data_02060500;
    menu->onUpdate(menu);
    if (menu->mode == 0) {
        target = menu->targets[menu->page - 1];
        previous = *target;
        applied = FALSE;
        if (pad & 0x302) {
            *target = menu->choice;
            if (menu->page == 3) {
                ApplySlotOffset(menu, *target);
            }
            applied = TRUE;
        }
        if (atTarget || applied) {
            StatPreview preview = sOv075_Empty_020d1568;

            if (atTarget && menu->noticeArmed != 0 && menu->noticePending != 0) {
                pad = 0;
                menu->noticePending = 0;
                menu->noticeArmed = 0;
                ShowDialogMessage(menu, 0x5f, 3, 0);
            }
            UpdateDirectionRepeat(menu);
            if (menu->onApply(menu, target, applied)) {
                pad |= 1;
            }
            if (previous != *target) {
                PlayerStats stats;

                ComputePlayerStats(data_0205fe0c, &stats, FALSE, 0);
                preview.level = stats.level;
                preview.maxHp = stats.hp;
                preview.attack = stats.strength;
                preview.defense = stats.magic;
                preview.magic = stats.defense;
                preview.capacity = stats.unk_c;
                RefreshStatusMenuData(data_0205fe0c, &preview);
            }
        }
    }
    if (atTarget && (pad & 1)) {
        if (menu->page != 3 || !(*menu->targets[2] >> 7)) {
            notice = GetOptionChangeNotice(menu);
            if (notice > 0) {
                ShowDialogMessage(menu, notice + 0x22, 2, 0);
            } else {
                CommitOptionChoice(menu, TRUE);
                PlaySoundEffect(1, 1);
                ShowNextUnlockNotice(menu, 1, 0);
                SetStatusPageAndCursor(3, -1);
            }
        } else {
            PlaySoundEffect(1, 4);
        }
    } else if (atTarget && (pad & 2)) {
        PlaySoundEffect(1, 3);
        ResetMatrixDescription(menu);
        ShowNextUnlockNotice(menu, 1, 0);
    } else if (pad & 0x200) {
        const PageTab *tabs;
        u8 type;
        u8 index;
        u8 count;
        u8 mask;
        u8 id;

        tabs = data_ov075_020d140a;
        type = menu->current->type;
        index = 0;
        if (type != 9) {
            do {
                index++;
            } while (type != tabs[index].id);
        }
        count = 5;
        mask = data_0205fe0c->unlockedPages;
        do {
            if (index == 0) {
                index = 5;
            }
            index--;
            id = tabs[index].id;
            if ((1 << (id - 9)) & mask) {
                OpenPage(menu, index, id);
                break;
            }
        } while (--count != 0);
    } else if (pad & 0x100) {
        const PageTab *tabs;
        u8 type;
        u8 index;
        u8 count;
        u8 mask;
        u8 id;

        tabs = data_ov075_020d140a;
        type = menu->current->type;
        index = 0;
        if (type != 9) {
            do {
                index++;
            } while (type != tabs[index].id);
        }
        count = 5;
        mask = data_0205fe0c->unlockedPages;
        do {
            index++;
            if (index == 5) {
                index = 0;
            }
            id = tabs[index].id;
            if ((1 << (id - 9)) & mask) {
                OpenPage(menu, index, id);
                break;
            }
        } while (--count != 0);
    }
    return 0;
}
