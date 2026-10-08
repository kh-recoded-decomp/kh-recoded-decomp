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

extern PartyGlobals data_ov001_020a04bc;
extern u8 data_020608c8;
extern char OVERLAY_51_ID[];
extern char OVERLAY_52_ID[];
extern char OVERLAY_56_ID[];
extern char OVERLAY_58_ID[];
extern void InitializeEntryGroupRegistry(void);
extern void func_ov001_0206c9c0(void);
extern void func_ov021_020a7cb0(void);
extern void LoadMsgContainers(void);
extern int *AcquireMapLayout(BOOL reload, BOOL discard);
extern void func_02029f8c(int processor, int overlayId);
extern int LoadOverlayForMode(unsigned int selectionIndex, int mode);
extern void func_ov021_020a7480(void *tracker, int index);
extern void LoadModeSprites(void);
extern void CreateFieldEffectGroups(void);
extern void ClearHandleActiveFlags(void);

void InitPartyState(int mode) {
    PartyState *party = data_ov001_020a04bc.party;
    int i;

    if (party->count > 0) {
        return;
    }
    if (data_020608c8 > 1) {
        mode = 2;
    }
    party->selected = mode;
    InitializeEntryGroupRegistry();
    func_ov001_0206c9c0();
    func_ov021_020a7cb0();
    LoadMsgContainers();
    AcquireMapLayout(FALSE, FALSE);
    func_02029f8c(0, (int)OVERLAY_51_ID);
    party->handles[0] = (int)OVERLAY_51_ID;
    if (party->selected != 1) {
        func_02029f8c(0, (int)OVERLAY_52_ID);
        party->handles[1] = (int)OVERLAY_52_ID;
        if (data_020608c8 == 1) {
            party->handles[2] = (int)OVERLAY_56_ID;
        } else if (data_020608c8 > 1) {
            party->handles[2] = (int)OVERLAY_58_ID;
        }
        if (party->handles[2] != -1) {
            func_02029f8c(0, party->handles[2]);
        }
    }
    for (i = 0; i < data_020608c8; i++) {
        PartyEntry *entry = &party->entries[i];
        party->count++;
        data_ov001_020a04bc.factory = NULL;
        entry->overlayId = LoadOverlayForMode(i, mode);
        if (data_ov001_020a04bc.factory != NULL) {
            entry->actor = data_ov001_020a04bc.factory(i);
            func_ov021_020a7480(entry->tracker, i);
            entry->flags |= 1;
            entry->flags |= 0x10;
        }
    }
    LoadModeSprites();
    CreateFieldEffectGroups();
    ClearHandleActiveFlags();
}
