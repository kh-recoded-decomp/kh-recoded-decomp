#include "nitro/types.h"

typedef struct ContactTarget {
    void *object;
    int kind;
} ContactTarget;

typedef struct ContactLink {
    void *other;
    int type;
} ContactLink;

typedef struct ContactInfo {
    u8 pad_00[0x68];
    ContactLink link;
} ContactInfo;

extern BOOL IsObjectInChain_020a3914(void *object, void *target);

BOOL CanUseContactTarget_020a44e8(ContactTarget *contact, void *object)
{
    ContactLink *link;
    int type;

    if (contact->kind == 4) {
        link = &((ContactInfo *)contact->object)->link;
        type = link->type;
        if (type != 6 && type != 7 && type != 0x1b && type != 0x1c && type != 8) {
            return FALSE;
        }
        if (type == 8 && IsObjectInChain_020a3914(object, link->other)) {
            return FALSE;
        }
    }
    return TRUE;
}
