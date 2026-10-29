#ifndef KH_RECODED_COLLISION_CONTACTS_H
#define KH_RECODED_COLLISION_CONTACTS_H

#include "nitro/types.h"
#include "nitro/fx_types.h"

/* Recovered workspace fields; projectionMode is not a contact-count field. */
typedef struct CollisionContacts {
    u8 reserved000[0xc0];
    VecFx32 normals[16];
    u8 count;
    u8 selected[3];
    u8 reserved184[0x1a1 - 0x184];
    u8 projectionMode;
} CollisionContacts;

typedef char CollisionContactsSizeCheck[sizeof(CollisionContacts) == 0x1a4 ? 1 : -1];

#endif
