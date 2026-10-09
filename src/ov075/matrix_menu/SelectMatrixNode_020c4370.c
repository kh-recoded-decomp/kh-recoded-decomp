#pragma opt_common_subs off
#include "nitro/types.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_BG1CNT (*(volatile u16 *)0x0400000a)

typedef enum { BG_SCREEN_SIZE_256x256 } BgScreenSize;
typedef enum { BG_COLOR_MODE_16, BG_COLOR_MODE_256 } BgColorMode;
typedef enum { BG_SCREEN_BASE_0000 } BgScreenBase;
typedef enum { BG_CHAR_BASE_00000, BG_CHAR_BASE_14000 = 5 } BgCharBase;
typedef enum { BG_EXT_PLTT_01 } BgExtPltt;

typedef struct MatrixNode {
    u16 index;
    u8 type;
    s8 requiredFlag;
    s16 lockValue;
    u16 bitIndex;
    u8 pendingSteps;
    u8 visited;
    u8 pad_0a[2];
    s16 links[4];
} MatrixNode;

typedef struct MatrixMap {
    u8 pad_0000[0x9c];
    MatrixNode *nodes[(0x24dc - 0x9c) / 4];
    s16 recordIds[1];
} MatrixMap;

typedef struct ItemSlot {
    u16 count;
    u8 pad_02[6];
    int *recordId;
} ItemSlot;

typedef struct RecordSlot {
    int recordId;
    u8 pad_04[0x2c];
} RecordSlot;

typedef struct StatusRequest {
    int words[6];
} StatusRequest;

typedef struct SaveData {
    u8 pad_0000[0x2c58];
    u32 equipMask;
    u32 unlockBits[2];
} SaveData;

typedef struct {
    u8 pad_00000[7];
    u8 listDirty;
    u8 pad_00008[0x40 - 8];
    s16 fadeStep;
    u8 pad_00042[0x7c - 0x42];
    BOOL linkLocked;
    u8 pad_00080[4];
    u8 panel[0x87c - 0x84];
    ItemSlot items[1501];
    u8 pad_04ed8[8];
    u8 pageTable[0x8018 - 0x4ee0];
    s32 panelValue;
    s16 panelCursor;
    u8 pad_0801e[0x11fac - 0x801e];
    void *currentPage;
    u8 pad_11fb0[0x12dd0 - 0x11fb0];
    MatrixMap *map;
    MatrixNode *node;
    u8 pad_12dd8[0x131a4 - 0x12dd8];
    void *layout;
    u8 pad_131a8[0x138f0 - 0x131a8];
    u8 effect[0x13e64 - 0x138f0];
    u16 eventFlags;
    u8 pad_13e66[0x13e7d - 0x13e66];
    u8 modeLabel;
    u8 pad_13e7e[0x13e84 - 0x13e7e];
    BOOL modeLocked;
    u8 pad_13e88[4];
    u8 *modeLabels[5];
    s32 mode;
    s32 modeParamA;
    s32 modeParamB;
    u8 pad_13eac[4];
    s32 modeTimer;
    u8 pad_13eb4[0x13ec4 - 0x13eb4];
    u8 modeSubState;
    u8 pad_13ec5[0x174f8 - 0x13ec5];
    s32 pendingAction;
    u8 pad_174fc[0x17518 - 0x174fc];
    BOOL modeConfirmed;
} MatrixMenu;

extern SaveData *data_0205fe0c;
extern u16 data_02060500;
extern const StatusRequest data_ov075_020d1518;
extern const s32 data_ov075_020d13f4[];
extern const s32 data_ov075_020d1408[];

extern int GetPackedBitMask(u32 *bitWords, int bitIndex);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov073_020c1eb4(SaveData *save, StatusRequest *request);
extern RecordSlot *GetRecordSlotPair1Entry_02051ef4(s32 index);
extern void func_ov073_020c2ca4(int state, int parameter);
extern void func_ov075_020d0014(void *panel, int owner);
extern int func_ov001_020644b0(void);
extern void ShowDialogMessage_020c8ce4(MatrixMenu *menu, int messageId, int dialogType, int cancelable);
extern void DecrementByteCounter_02029370(int index);
extern int *func_01ffb2f8(void *effect, int kind, int arg);
extern BOOL func_ov075_020c4260(MatrixMenu *menu);
extern void func_ov075_020c5d10(MatrixMenu *menu, int a, int b, int c);
extern void SetSecondaryElementEnabled_020bc084(BOOL enabled);
extern void SetUnlockableElementsVisible_020d0e64(void *layout, BOOL visible);
extern BOOL IsMenuModeUnlocked_020c4324(int mode);
extern void *func_ov027_020ba2a8(void *table, int idx);
extern void ResetDirectionRepeat_020c430c(MatrixMenu *menu);

static inline void SetBg1Control(BgScreenSize screenSize, BgColorMode colorMode, BgScreenBase screenBase,
                                 BgCharBase charBase, BgExtPltt bgExtPltt)
{
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | (screenSize << 14) | (colorMode << 7) | (screenBase << 8) |
                       (charBase << 2) | (bgExtPltt << 13));
}

static inline BOOL IsNodeFlagSet(MatrixNode *node)
{
    if (GetPackedBitMask(data_0205fe0c->unlockBits, node->requiredFlag)) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL IsLinkLocked(MatrixMenu *menu, int link)
{
    MatrixNode *child;
    BOOL locked;

    if (link >= 0) {
        child = menu->map->nodes[link];
        locked = FALSE;
        if (child->type >= 14 && child->requiredFlag >= 0 && !IsNodeFlagSet(child)) {
            locked = TRUE;
        }
    } else {
        locked = FALSE;
    }
    return locked ? TRUE : FALSE;
}

static inline BOOL CanEnterNode(MatrixMenu *menu, MatrixNode *node)
{
    s16 *link;
    MatrixNode *child;
    int i;

    if (node->lockValue >= 0) {
        return TRUE;
    }
    link = node->links;
    for (i = 0; i < 4; i++, link++) {
        if (*link < 0) {
            continue;
        }
        child = menu->map->nodes[*link];
        if (child->type == 3 || (child->pendingSteps == 0 && (child->requiredFlag < 0 || IsNodeFlagSet(child)))) {
            return TRUE;
        }
    }
    return FALSE;
}

static inline void *GetPage(MatrixMenu *menu, int index)
{
    if (index >= 0) {
        return func_ov027_020ba2a8(menu->pageTable, index);
    }
    return NULL;
}

static inline void ShowStatusPage(int cursor, int page)
{
    func_ov073_020c2ca4(page, cursor);
}

static inline void ToggleEquipBit(u16 bit)
{
    data_0205fe0c->equipMask ^= 1 << bit;
}

void SelectMatrixNode_020c4370(MatrixMenu *menu)
{
    BOOL playSound = TRUE;
    MatrixNode *node = menu->node;
    ItemSlot *slot;
    StatusRequest request;
    int bit;
    s16 recordId;
    int tableIndex;
    u32 planes;
    int messageId;
    int dialogType;
    int pageIndex;
    int labelIndex;
    int cursor;
    BOOL notMode;

    switch (node->type) {
    case 6:
        bit = node->bitIndex;
        recordId = menu->map->recordIds[bit];
        if (node->pendingSteps != 0 || (recordId >= 0xf8 && recordId <= 0xfb)) {
            goto fail;
        }
        request = data_ov075_020d1518;
        ToggleEquipBit(bit);
        func_ov073_020c1eb4(data_0205fe0c, &request);
        PlaySoundEffect_0204d924(1, 1);
        func_ov073_020c1eb4(data_0205fe0c, NULL);
        ShowStatusPage(GetRecordSlotPair1Entry_02051ef4(menu->map->recordIds[bit])->recordId, 2);
        break;
    fail:
        PlaySoundEffect_0204d924(1, 4);
        break;
    case 1:
        menu->linkLocked = IsLinkLocked(menu, menu->node->links[1]) || IsLinkLocked(menu, menu->node->links[0]) ||
                           IsLinkLocked(menu, menu->node->links[2]) || IsLinkLocked(menu, menu->node->links[3]);
    case 2:
        if (CanEnterNode(menu, menu->node)) {
            SetBg1Control(BG_SCREEN_SIZE_256x256, BG_COLOR_MODE_16, BG_SCREEN_BASE_0000, BG_CHAR_BASE_14000,
                          BG_EXT_PLTT_01);
            planes = (REG_DISPCNT & 0x1f00) >> 8;
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | ((planes | 2) << 8);
            menu->panelValue = menu->node->lockValue;
            menu->panelCursor = -1;
            func_ov075_020d0014(menu->panel, 0);
            menu->fadeStep += 5;
        } else {
            PlaySoundEffect_0204d924(1, 4);
        }
        break;
    case 9:
        if (func_ov001_020644b0() != 400) {
            notMode = TRUE;
        } else {
            notMode = FALSE;
        }
        if (menu->modeConfirmed != 0 || notMode) {
            menu->mode = 1;
            playSound = notMode;
            menu->modeConfirmed = 0;
        } else {
            PlaySoundEffect_0204d924(1, 1);
            ShowDialogMessage_020c8ce4(menu, 0x5f, 3, 1);
        }
        break;
    case 10:
        menu->mode = 5;
        break;
    case 11:
        menu->modeSubState = 0;
        menu->mode = 4;
        break;
    case 12:
        menu->mode = 2;
        break;
    case 13:
        menu->mode = 3;
        break;
    case 4:
    case 5:
        slot = &menu->items[node->type == 4 ? 0x160 : 0x161];
        if (menu->pendingAction == 1) {
            DecrementByteCounter_02029370(*slot->recordId);
            slot->count--;
            menu->currentPage = NULL;
            menu->listDirty = TRUE;
            menu->eventFlags |= 0x100;
            func_01ffb2f8(menu->effect, 2, 0);
            func_01ffb2f8(menu->effect, 4, 0);
            if (func_ov075_020c4260(menu)) {
                func_ov075_020c5d10(menu, -1, -1, 0x18);
            }
            SetSecondaryElementEnabled_020bc084(FALSE);
            SetUnlockableElementsVisible_020d0e64(menu->layout, FALSE);
            break;
        }
        if (slot->count != 0) {
            messageId = 4;
            dialogType = 1;
            PlaySoundEffect_0204d924(1, 1);
        } else {
            messageId = 5;
            dialogType = 0;
            PlaySoundEffect_0204d924(1, 4);
        }
        ShowDialogMessage_020c8ce4(menu, messageId, dialogType, 0);
        break;
    }

    if (menu->mode == 0) {
        return;
    }
    if (IsMenuModeUnlocked_020c4324(menu->mode)) {
        pageIndex = 0;
        labelIndex = 0;
        cursor = 0;
        switch (menu->node->type) {
        case 9:
            pageIndex = 0;
            break;
        case 12:
            pageIndex = 3;
            labelIndex = 1;
            cursor = 2;
            break;
        case 13:
            pageIndex = 4;
            labelIndex = 2;
            cursor = 3;
            break;
        case 11:
            pageIndex = 2;
            labelIndex = 3;
            cursor = 6;
            break;
        case 10:
            pageIndex = 1;
            labelIndex = 4;
            cursor = 7;
            break;
        }
        if (playSound) {
            PlaySoundEffect_0204d924(1, 1);
        }
        if (pageIndex == 0) {
            menu->modeLocked = TRUE;
        }
        func_ov073_020c2ca4(3, cursor);
        menu->currentPage = GetPage(menu, pageIndex + 0x1b);
        menu->listDirty = TRUE;
        tableIndex = menu->mode - 1;
        menu->modeParamA = data_ov075_020d13f4[tableIndex];
        menu->modeParamB = data_ov075_020d1408[tableIndex];
        SetUnlockableElementsVisible_020d0e64(menu->layout, FALSE);
        menu->modeLabel = *menu->modeLabels[labelIndex];
        ResetDirectionRepeat_020c430c(menu);
        menu->modeTimer = 0;
        menu->modeLocked = (func_ov001_020644b0() == 400 && menu->mode != 1) ? TRUE : FALSE;
        data_02060500 = 0;
        return;
    }
    PlaySoundEffect_0204d924(1, 4);
    menu->mode = 0;
}
