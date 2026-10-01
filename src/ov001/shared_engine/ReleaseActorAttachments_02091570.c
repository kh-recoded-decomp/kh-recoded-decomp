#include "nitro/types.h"

typedef struct {
    u8 pad[0x32];
    u16 nextId : 12;
    u16 kind : 4;
} Attachment;

typedef struct {
    u8 pad[0x286];
    u16 firstAttachmentId;
} Actor;

extern Attachment *GetStageAttachment_0209c144(u32 id);
extern int ReleaseStageSlotEntry_0209c024(int index, int slot);

void ReleaseActorAttachments_02091570(Actor *actor) {
    u16 id = actor->firstAttachmentId;
    if (id != 0) {
        while (id != 0) {
            Attachment *attachment = GetStageAttachment_0209c144(id);
            if (attachment != NULL) {
                u16 next = attachment->nextId;
                ReleaseStageSlotEntry_0209c024(6, id);
                id = next;
            }
        }
        actor->firstAttachmentId = 0;
    }
}
