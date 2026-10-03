#include "nitro/types.h"

typedef struct HandleConfig {
    u8 pad0[0x1a];
    u8 primaryBonus;
    u8 secondaryBonus;
} HandleConfig;

typedef struct ObjHandle {
    u32 flags;
    u8 playerId;
    u8 pad5[3];
    HandleConfig *config;
    u8 padC[0x54];
    void *active;
    int limit;
} ObjHandle;

extern int GetObjHandleLevel_020aa6e4(ObjHandle *handle, int which);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern int GetPlayerEntryCount_02050050(int player, u32 id);

BOOL IsObjHandleOverLimit_020aa674(ObjHandle *handle)
{
    int level;
    HandleConfig *config = handle->config;

    if (handle->active == NULL) {
        return FALSE;
    }
    if (handle->flags & 1) {
        level = GetObjHandleLevel_020aa6e4(handle, 0);
        level += config->primaryBonus;
        if (IsPlayerEntryFlagSet_02050014(handle->playerId, 0x14)) {
            level += GetPlayerEntryCount_02050050(handle->playerId, 0x14);
        }
    } else if (handle->flags & 2) {
        level = GetObjHandleLevel_020aa6e4(handle, 1);
        level += config->secondaryBonus;
        if (IsPlayerEntryFlagSet_02050014(handle->playerId, 0x14)) {
            level += GetPlayerEntryCount_02050050(handle->playerId, 0x14);
        }
    }
    if (!(handle->flags & 0x10) && level > handle->limit) {
        return TRUE;
    }
    return FALSE;
}
