#include "nitro/types.h"

typedef struct FieldPlayer FieldPlayer;

struct FieldPlayer {
    u8 pad_000[0x1d8];
    u8 slotIndex;
    u8 pad_1d9[0x20c - 0x1d9];
    void (*onStateChange)(FieldPlayer *player, int state, int flag);
    void (*onActivate)(FieldPlayer *player, int arg);
};

typedef struct {
    u8 pad_00[8];
    u8 cell[0x24 - 0x08];
    u16 flags;
    u8 pad_26[2];
} FieldPlayerEntry;

typedef struct {
    s32 mode;
    FieldPlayerEntry entries[1];
} FieldPlayerSet;

extern FieldPlayerSet *data_ov001_020a049c;

extern FieldPlayer *GetBoundedEntryField_0206db5c(int index);
extern void func_ov021_020a74f0(void *cell);
extern void func_ov001_0206cab4(int enabled);
extern void func_020359f8(int index, int param2, int param3);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void UpdateActionCommand_0206d0ac(FieldPlayer *player);
extern void RefreshFieldMenuPage_0206d248(FieldPlayer *player);

void ActivateFieldPlayerEntry_0206dd90(int index, u32 param, u16 arg) {
    FieldPlayerSet *set = data_ov001_020a049c;
    FieldPlayerEntry *entry;
    FieldPlayer *current;
    FieldPlayer *player;

    if (set != NULL && (player = GetBoundedEntryField_0206db5c(index)) != NULL) {
        entry = &set->entries[index];
        entry->flags |= 2;
        entry->flags |= 8;
        entry->flags &= 0xffef;
        func_ov021_020a74f0(entry->cell);
        current = GetBoundedEntryField_0206db5c(index);
        if (current->onStateChange != NULL) {
            current->onStateChange(current, 2, 1);
        }
        func_ov001_0206cab4(0);
        func_020359f8(player->slotIndex, 0, param);
        ActorSlot_SetFlag8ByIndex_02036120(player->slotIndex, FALSE);
        if (player->onActivate != NULL) {
            player->onActivate(player, arg);
        }
        if (index == 0) {
            switch (set->mode) {
            case 0:
            case 2:
                UpdateActionCommand_0206d0ac(player);
                break;
            case 1:
                RefreshFieldMenuPage_0206d248(player);
                break;
            }
        }
    }
}
