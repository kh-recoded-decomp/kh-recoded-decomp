#include "nitro/types.h"

typedef struct ListPageInfo {
    s32 entryCount;
    u8 pad04[0x4c - 4];
} ListPageInfo;

/* Paging view of the list scene; each list has a 0x4c-byte descriptor. */
typedef struct ListPageState {
    s32 activeList;
    s32 activePage;
    u8 pad08[0xd034 - 8];
    ListPageInfo lists[40];
} ListPageState;

extern BOOL IsStateFlagSet(int setIndex, int bitIndex);
extern void SetOv101SlotEntryVisible(int listIndex, int entryIndex,
                                   int visible, ListPageState *state);
extern void PlaySoundEffect(int bank, int sound);

void ToggleListPage(ListPageState *state)
{
    int list = state->activeList;
    int visible;

    if (!IsStateFlagSet(0, list) || state->lists[list].entryCount <= 9) {
        return;
    }
    state->activePage = (state->activePage + 1) % 2;
    visible = 1;
    if (state->activePage == 1) {
        visible = 0;
    }
    SetOv101SlotEntryVisible(0, 0, visible, state);
    PlaySoundEffect(0, 1);
}
