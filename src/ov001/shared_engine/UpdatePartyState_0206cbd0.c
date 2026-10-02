#include "nitro/types.h"

typedef struct ActorProfile {
    u16 unk0;
    u16 characterId;
    u16 level;
} ActorProfile;

typedef struct PartyActor {
    u8 pad_000[0x1d4];
    ActorProfile *profile;
} PartyActor;

typedef struct PartyEntry {
    int id;
    PartyActor *actor;
    u8 pad_08[0x1c];
    u16 flags;
    u8 pad_26[2];
} PartyEntry;

typedef struct PartyState {
    int selected;
    PartyEntry entries[3];
    int count;
} PartyState;

typedef struct StatusRecord {
    u8 pad_0[4];
    u16 value;
} StatusRecord;

extern PartyState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern BOOL func_ov021_020af3e8(void);
extern u8 func_ov001_0207b45c(void);
extern BOOL Camera_IsFlag19Set_020c14e0(void);
extern void TogglePanelFormation_0207b428(void);
extern StatusRecord *func_0205125c(void);
extern u8 *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern s32 ScaleByKindAndMode_0204fd24(int kind, s32 value);
extern int func_ov001_0207162c(int index, int level, int characterId, int scaled);
extern BOOL IsHudFlag9Set_02072884(void);
extern void func_ov035_020bc250(int index, int characterId);
extern void func_ov001_02074fa8(int index, int characterId, int mode);
extern void RefreshActiveMenuEntry_02074f7c(int index, int x, int y);
extern void UpdatePrimaryEventRecord_0206cd9c(void);
extern void func_ov001_0206d2dc(void);

int UpdatePartyState_0206cbd0(void) {
    PartyState *party = NNSi_FndGetCurrentRootHeap_0202a764();
    int i;

    if (party->entries[0].actor != NULL && (party->entries[0].flags & 0x10) <= 0) {
        BOOL ready = TRUE;
        if (func_ov021_020af3e8()) {
            ready = FALSE;
        }
        if (ready) {
            BOOL toggle = FALSE;
            if (func_ov001_0207b45c() == 1 && !Camera_IsFlag19Set_020c14e0()) {
                toggle = TRUE;
            } else if (func_ov001_0207b45c() == 2 && Camera_IsFlag19Set_020c14e0()) {
                toggle = TRUE;
            }
            if (toggle) {
                TogglePanelFormation_0207b428();
            }
        }
    }
    for (i = 0; i < party->count; i++) {
        PartyEntry *entry = &party->entries[i];
        if (entry->actor != NULL) {
            StatusRecord *status = func_0205125c();
            u8 *selection = GetOverlaySelectionRecord(i);
            u16 level = entry->actor->profile->level;
            s32 scaled = ScaleByKindAndMode_0204fd24(*selection, status->value);
            u16 characterId;
            func_ov001_0207162c(i, level, entry->actor->profile->characterId, scaled);
            characterId = entry->actor->profile->characterId;
            if (IsHudFlag9Set_02072884()) {
                func_ov035_020bc250(i, characterId);
                func_ov001_02074fa8(i, characterId, 7);
            } else {
                RefreshActiveMenuEntry_02074f7c(i, characterId, 7);
            }
        }
    }
    switch (party->selected) {
    case 0:
    case 2:
        UpdatePrimaryEventRecord_0206cd9c();
        break;
    case 1:
        func_ov001_0206d2dc();
        break;
    }
    return 0;
}
