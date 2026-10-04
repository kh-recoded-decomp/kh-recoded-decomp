#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x63c6];
    s8 cursor;
} Ov081State;

extern Ov081State *data_020c5d80;
extern void SkipToUnlockedListEntry_020c5a74(Ov081State *state, BOOL forward);
extern void BindDescriptor0_020c5640(void *obj);
extern void BindDescriptor0_020c4de8(void *obj);
extern void *FX_Div_020c542c(void);
extern void DrawListTitle_020c56a8(Ov081State *state, void *list);

void ResetListCursor_020c5c0c(void)
{
    Ov081State *state;

    data_020c5d80->cursor = 0;
    SkipToUnlockedListEntry_020c5a74(data_020c5d80, TRUE);
    state = data_020c5d80;
    DrawListTitle_020c56a8(state, FX_Div_020c542c());
    BindDescriptor0_020c5640(state);
    BindDescriptor0_020c4de8(data_020c5d80);
}
