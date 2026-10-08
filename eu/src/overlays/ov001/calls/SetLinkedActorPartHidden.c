#include "nitro/types.h"

typedef struct LinkedPart {
    u8 pad[0xc];
    u8 flags;
} LinkedPart;

typedef struct LinkedOwner {
    u8 pad[0x128];
    u8 flags;
} LinkedOwner;

extern LinkedPart *GetFirstLinkedActor(LinkedOwner *actor);
extern LinkedPart *GetNextLinkedActor(LinkedPart *actor);

void SetLinkedActorPartHidden(LinkedOwner *owner, int index, BOOL visible) {
    LinkedPart *part = GetFirstLinkedActor(owner);
    u16 i = 0;

    if (index == 0) {
        if (!visible) {
            owner->flags |= 2;
        } else {
            owner->flags &= ~2;
        }
    }
    while (part != NULL) {
        if (i == index) {
            if (!visible) {
                part->flags |= 2;
            } else {
                part->flags &= ~2;
            }
            return;
        }
        part = GetNextLinkedActor(part);
        i++;
    }
}
