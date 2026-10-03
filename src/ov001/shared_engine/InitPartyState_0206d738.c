#include "nitro/types.h"

typedef struct PartyActor PartyActor;
typedef PartyActor *(*PartyActorFactory)(int index);

typedef struct PartyEntry {
    int overlayId;
    PartyActor *actor;
    u8 tracker[0x1c];
    u16 flags;
    u8 pad_26[2];
} PartyEntry;

typedef struct PartyState {
    int selected;
    PartyEntry entries[3];
    int count;
    int handles[3];
} PartyState;

typedef struct PartyGlobals {
    PartyState *party;
    PartyActorFactory factory;
} PartyGlobals;

extern PartyGlobals data_ov001_020a049c;
extern u8 data_020608c8;
extern char OverlayId51_00000033[];
extern char OverlayId52_00000034[];
extern char OverlayId56_00000038[];
extern char OverlayId58_0000003a[];
extern void func_ov021_020a88f8(void);
extern void func_ov001_0206c9c0(void);
extern void func_ov021_020a7c90(void);
extern void func_ov021_020a9524(void);
extern int *AcquireMapLayout_020506dc(BOOL reload, BOOL discard);
extern void func_02029f78(int processor, int overlayId);
extern int LoadOverlayForMode(unsigned int selectionIndex, int mode);
extern void func_ov021_020a7460(void *tracker, int index);
extern void LoadModeSprites_0206d308(void);
extern void CreateFieldEffectGroups_0206d628(void);
extern void ClearHandleActiveFlags_0204ffd0(void);

void InitPartyState_0206d738(int mode) {
    PartyState *party = data_ov001_020a049c.party;
    int i;

    if (party->count > 0) {
        return;
    }
    if (data_020608c8 > 1) {
        mode = 2;
    }
    party->selected = mode;
    func_ov021_020a88f8();
    func_ov001_0206c9c0();
    func_ov021_020a7c90();
    func_ov021_020a9524();
    AcquireMapLayout_020506dc(FALSE, FALSE);
    func_02029f78(0, (int)OverlayId51_00000033);
    party->handles[0] = (int)OverlayId51_00000033;
    if (party->selected != 1) {
        func_02029f78(0, (int)OverlayId52_00000034);
        party->handles[1] = (int)OverlayId52_00000034;
        if (data_020608c8 == 1) {
            party->handles[2] = (int)OverlayId56_00000038;
        } else if (data_020608c8 > 1) {
            party->handles[2] = (int)OverlayId58_0000003a;
        }
        if (party->handles[2] != -1) {
            func_02029f78(0, party->handles[2]);
        }
    }
    for (i = 0; i < data_020608c8; i++) {
        PartyEntry *entry = &party->entries[i];
        party->count++;
        data_ov001_020a049c.factory = NULL;
        entry->overlayId = LoadOverlayForMode(i, mode);
        if (data_ov001_020a049c.factory != NULL) {
            entry->actor = data_ov001_020a049c.factory(i);
            func_ov021_020a7460(entry->tracker, i);
            entry->flags |= 1;
            entry->flags |= 0x10;
        }
    }
    LoadModeSprites_0206d308();
    CreateFieldEffectGroups_0206d628();
    ClearHandleActiveFlags_0204ffd0();
}
