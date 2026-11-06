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

extern PartyGlobals gManagedActorGlobals;
extern u8 gSelectionRuntimeHeader;
extern char OVERLAY_51_ID[];
extern char OVERLAY_52_ID[];
extern char OVERLAY_56_ID[];
extern char OVERLAY_58_ID[];
extern void InitializeEntryGroupRegistry(void);
extern void EnsureFieldMessageLoaderManager(void);
extern void OpenCharacterSoundCueArchive(void);
extern void LoadMsgContainers(void);
extern int *AcquireMapLayout(BOOL reload, BOOL discard);
extern void LoadOverlayAfterGeometryTransfer(int processor, int overlayId);
extern int LoadOverlayForMode(unsigned int selectionIndex, int mode);
extern void InitFieldButtonForEntryIndex(void *tracker, int index);
extern void LoadModeSprites(void);
extern void CreateFieldEffectGroups(void);
extern void ClearHandleActiveFlags(void);

void InitPartyState(int mode) {
    PartyState *party = gManagedActorGlobals.party;
    int i;

    if (party->count > 0) {
        return;
    }
    if (gSelectionRuntimeHeader > 1) {
        mode = 2;
    }
    party->selected = mode;
    InitializeEntryGroupRegistry();
    EnsureFieldMessageLoaderManager();
    OpenCharacterSoundCueArchive();
    LoadMsgContainers();
    AcquireMapLayout(FALSE, FALSE);
    LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_51_ID);
    party->handles[0] = (int)OVERLAY_51_ID;
    if (party->selected != 1) {
        LoadOverlayAfterGeometryTransfer(0, (int)OVERLAY_52_ID);
        party->handles[1] = (int)OVERLAY_52_ID;
        if (gSelectionRuntimeHeader == 1) {
            party->handles[2] = (int)OVERLAY_56_ID;
        } else if (gSelectionRuntimeHeader > 1) {
            party->handles[2] = (int)OVERLAY_58_ID;
        }
        if (party->handles[2] != -1) {
            LoadOverlayAfterGeometryTransfer(0, party->handles[2]);
        }
    }
    for (i = 0; i < gSelectionRuntimeHeader; i++) {
        PartyEntry *entry = &party->entries[i];
        party->count++;
        gManagedActorGlobals.factory = NULL;
        entry->overlayId = LoadOverlayForMode(i, mode);
        if (gManagedActorGlobals.factory != NULL) {
            entry->actor = gManagedActorGlobals.factory(i);
            InitFieldButtonForEntryIndex(entry->tracker, i);
            entry->flags |= 1;
            entry->flags |= 0x10;
        }
    }
    LoadModeSprites();
    CreateFieldEffectGroups();
    ClearHandleActiveFlags();
}
