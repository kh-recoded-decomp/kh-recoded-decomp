#include "nitro/types.h"

typedef struct IdOwner {
    u8 pad_00[0x20];
    int id;
} IdOwner;

extern void func_ov021_020a7be0(IdOwner *owner, int id);

void ResetIfIdMatches_020a8178(IdOwner *owner, int id)
{
    if (owner->id == id) {
        func_ov021_020a7be0(owner, -1);
    }
}
