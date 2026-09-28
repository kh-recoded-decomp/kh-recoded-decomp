#include "nitro/types.h"

typedef struct AttachOwner {
    u8 pad_000[0x286];
    u16 attachedId;
} AttachOwner;

extern void *func_ov001_0209c144(u16 id);

void *GetAttachedObject_0208f724(AttachOwner *owner)
{
    if (owner == NULL) {
        return NULL;
    }
    if (owner->attachedId == 0) {
        return NULL;
    }
    return func_ov001_0209c144(owner->attachedId);
}
