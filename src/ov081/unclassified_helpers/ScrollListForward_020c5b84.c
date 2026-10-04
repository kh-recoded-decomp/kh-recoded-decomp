#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x63c6];
    s8 cursor;
} Ov081State;

typedef struct {
    u8 kind;
    u8 count;
} EntryList;

extern Ov081State *data_020c5d80;
extern EntryList *FX_Div_020c542c(void);
extern void SkipToUnlockedListEntry_020c5a74(Ov081State *state, BOOL forward);
extern void DrawListTitle_020c56a8(Ov081State *state, EntryList *list);
extern void BindDescriptor0_020c5640(void *obj);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void ScrollListForward_020c5b84(Ov081State *state)
{
    EntryList *list = FX_Div_020c542c();
    Ov081State *current;
    s8 previous;

    if (list->kind == 1) {
        previous = state->cursor;
        state->cursor = (previous + 1) % list->count;
        SkipToUnlockedListEntry_020c5a74(state, TRUE);
        if (state->cursor != previous) {
            current = data_020c5d80;
            DrawListTitle_020c56a8(current, FX_Div_020c542c());
            BindDescriptor0_020c5640(current);
            PlaySoundEffect_0204d924(0, 2);
        }
    }
}
