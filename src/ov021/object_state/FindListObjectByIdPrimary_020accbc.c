#include "nitro/types.h"

typedef struct {
    u32 unk_00;
    int id;
} ListObject;

typedef struct {
    u8 pad_00[0x4c];
    u8 list[0xc];
} ListOwner;

extern void *NNS_FndGetNextListObject_02012a38(void *list, void *object);

ListObject *FindListObjectByIdPrimary_020accbc(ListOwner *owner, int id) {
    ListObject *object;
    ListObject *next;

    for (object = NNS_FndGetNextListObject_02012a38(owner->list, NULL); object != NULL; object = next) {
        next = NNS_FndGetNextListObject_02012a38(owner->list, object);
        if (object->id == id) {
            break;
        }
    }
    return object;
}
