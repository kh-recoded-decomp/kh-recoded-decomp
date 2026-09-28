#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0x647c];
    u8 panel[0x647c];
    u8 primaryElement[0x4c];
    u8 secondaryElement[0xd4];
    BOOL primaryEnabled;
    BOOL secondaryEnabled;
} Ov039State;

extern Ov039State *data_ov039_020bea00;
extern void SetFlagBit0_020b85a8(u8 *element, BOOL enable);

void SetPrimaryElementEnabled_020bc054(BOOL enabled)
{
    Ov039State *state = data_ov039_020bea00;

    SetFlagBit0_020b85a8(state->primaryElement, enabled);
    state->primaryEnabled = enabled;
}
