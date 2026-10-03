#include "nitro/types.h"

typedef struct ItemInfo {
    u8 pad_00[0x4];
    s32 locked;
    u8 pad_08[0x18];
    s32 effect;
} ItemInfo;

typedef struct ItemSlotEntry {
    u16 count;
    u8 pad_02[0x6];
    ItemInfo *info;
} ItemSlotEntry;

typedef struct FieldContext {
    u8 pad_000[0x214];
    u32 unk_214_0 : 13;
    u32 itemsBlocked : 1;
} FieldContext;

typedef struct SaveState {
    u8 pad_0000[0x28d5];
    s8 worldId;
} SaveState;

extern FieldContext *data_ov001_020a0460;
extern SaveState *data_0205fe0c;
extern s8 GetCtxModeByte_02068084(void);
extern BOOL func_ov077_020c7a48(void);
extern BOOL IsPartyLevelSufficient_020c7a78(void);
extern BOOL func_ov077_020c7b14(void);
extern BOOL func_ov077_020c7b50(void);

static inline BOOL IsItemUseRestricted(void)
{
    BOOL restricted = FALSE;

    if (GetCtxModeByte_02068084() == 3) {
        BOOL outside = FALSE;
        if (data_0205fe0c->worldId != 0x1d && data_0205fe0c->worldId != 0x1e) {
            outside = TRUE;
        }
        if (outside) {
            restricted = TRUE;
        }
    }
    return restricted;
}

BOOL CanUseItemEntry_020c7b6c(ItemSlotEntry *entry)
{
    BOOL usable = TRUE;

    if (data_ov001_020a0460->itemsBlocked) {
        return FALSE;
    }
    if (entry->info->locked != 0 || entry->count == 0) {
        usable = FALSE;
    } else {
        switch (entry->info->effect) {
        case 0xb7:
        case 0xb8:
            if (func_ov077_020c7a48()) {
                usable = FALSE;
            }
            break;
        case 0xb9:
        case 0xba:
            if (IsItemUseRestricted()) {
                usable = FALSE;
            } else if (func_ov077_020c7b50()) {
                usable = FALSE;
            } else {
                usable = !IsPartyLevelSufficient_020c7a78();
            }
            break;
        case 0xbd:
            if (IsItemUseRestricted()) {
                usable = FALSE;
            }
            if (IsPartyLevelSufficient_020c7a78() && func_ov077_020c7a48() && func_ov077_020c7b14()) {
                usable = FALSE;
            }
            break;
        case 0xbc:
            if (IsItemUseRestricted()) {
                usable = FALSE;
            }
            if (func_ov077_020c7a48() && func_ov077_020c7b14()) {
                usable = FALSE;
            }
            break;
        case 0xbb:
            if (IsItemUseRestricted()) {
                usable = FALSE;
            }
            if (func_ov077_020c7b14()) {
                usable = FALSE;
            }
            break;
        }
    }
    return usable;
}