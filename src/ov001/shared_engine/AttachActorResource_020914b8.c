#include "nitro/types.h"

typedef struct Attachment {
    u8 pad_00[0x30];
    u16 resourceIndex;
    union {
        u16 bits;
        struct {
            u16 nextId : 12;
            u16 isDefault : 1;
            u16 visible : 1;
            u16 reserved : 2;
        };
    };
} Attachment;

typedef struct StageActor {
    u8 pad_000[0x286];
    u16 firstAttachmentId;
} StageActor;

extern char data_ov001_020a0274[];
extern int ReleaseStageSlot_0209c008(int kind);
extern Attachment *GetStageAttachment_0209c144(u32 id);
extern void func_01ff88c4(void *dst, u32 value, u32 size);
extern u16 FindActorResourceIndexByName_02091248(StageActor *actor, const char *name);
extern int String_CompareBounded_020220bc(const char *a, const char *b, int length);

void AttachActorResource_020914b8(StageActor *actor, const char *name, int isDefault, int visible)
{
    int id;
    int linkId;
    Attachment *attachment;
    Attachment *link;

    id = ReleaseStageSlot_0209c008(6);
    if (id == 0) {
        return;
    }
    attachment = GetStageAttachment_0209c144(id);
    if (attachment == NULL) {
        return;
    }
    func_01ff88c4(attachment, 0, sizeof(Attachment));
    linkId = actor->firstAttachmentId;
    if (linkId == 0) {
        actor->firstAttachmentId = id;
    } else {
        while (linkId != 0) {
            link = GetStageAttachment_0209c144(linkId);
            if (link == NULL) {
                break;
            }
            linkId = link->nextId;
            if (linkId == 0) {
                link->bits = (link->bits & ~0xfff) | (id & 0xfff);
                break;
            }
        }
    }
    if (attachment == NULL) {
        return;
    }
    attachment->resourceIndex = FindActorResourceIndexByName_02091248(actor, name);
    if (isDefault == 0) {
        isDefault = String_CompareBounded_020220bc(name, data_ov001_020a0274, 3) == 0;
    }
    attachment->isDefault = (u16)isDefault;
    attachment->visible = (u16)visible;
}
