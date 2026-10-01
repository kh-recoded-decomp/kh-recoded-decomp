#include "nitro/types.h"

typedef struct QuadTreeOwner {
    u32 unk_00;
    int **tree;
} QuadTreeOwner;

typedef struct Attachment {
    u8 pad_00[0x24];
    u8 buffer[0x7e];
    u16 nextId;
} Attachment;

typedef struct AttachOwner {
    u8 pad_000[0x284];
    u16 firstAttachmentId;
} AttachOwner;

extern QuadTreeOwner *func_02036230(AttachOwner *owner);
extern Attachment *func_ov001_0209c168(u32 id);
extern void FreeStateBuffer_020418dc(void *buffer);
extern void QuadTree_RemoveObject_02033c60(int *tree, Attachment *object);
extern int ReleaseStageSlotEntry_0209c024(int index, int slot);

void ReleaseAllAttachments_02091400(AttachOwner *owner)
{
    QuadTreeOwner *grid = func_02036230(owner);
    u32 id;

    if (grid == NULL) {
        return;
    }
    id = owner->firstAttachmentId;
    if (id == 0) {
        return;
    }
    while (id != 0) {
        Attachment *attachment = func_ov001_0209c168(id);

        if (attachment != NULL) {
            u32 nextId = attachment->nextId;

            FreeStateBuffer_020418dc(attachment->buffer);
            QuadTree_RemoveObject_02033c60(*grid->tree, attachment);
            ReleaseStageSlotEntry_0209c024(7, id);
            id = nextId;
        }
    }
    owner->firstAttachmentId = 0;
}
