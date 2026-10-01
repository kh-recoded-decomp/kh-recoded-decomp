#include "nitro/types.h"

typedef struct LinkedPart {
    u8 pad[0xc];
    u8 flags;
} LinkedPart;

typedef struct LinkedOwner {
    u8 pad[0x128];
    u8 flags;
} LinkedOwner;

extern LinkedPart *GetFirstLinkedActor_0208f6e8(LinkedOwner *actor);
extern LinkedPart *GetNextLinkedActor_0208f708(LinkedPart *actor);

void SetLinkedActorPartHidden_02091454(LinkedOwner *owner, int index, BOOL visible) {
    LinkedPart *part = GetFirstLinkedActor_0208f6e8(owner);
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
        part = GetNextLinkedActor_0208f708(part);
        i++;
    }
}
