#include "nitro/types.h"

typedef struct QuadTreeHolder {
    void *tree;
} QuadTreeHolder;

typedef struct ActorContext {
    u8 pad_00[4];
    QuadTreeHolder *quadTree;
} ActorContext;

typedef struct FieldObject FieldObject;
typedef int (*StateFunc)(FieldObject *object);

struct FieldObject {
    u8 pad_00[0xc];
    u8 *objectClass;
    u8 pad_10[4];
    StateFunc stateUpdate;
    u8 pad_18[0x36];
    u16 flags;
    u8 pad_50[8];
    s32 state;
    u8 pad_5c[8];
    s32 frame;
};

extern int FSi_CloseFileCommand_020a0ec8(FieldObject *object);
extern int FieldObject_AdvanceToAnimEnd_020a0ecc(FieldObject *object);
extern int FSi_CloseFileCommand_020a0ef8(FieldObject *object);
extern ActorContext *func_02036230(void);
extern void QuadTree_RemoveObject_02033c60(void *tree, void *object);
extern void SetObjectAnimTrack_0207f8d0(FieldObject *object, s8 track);

void FieldObject_SetState_020a06e8(FieldObject *object, int state)
{
    object->state = state;
    switch (state) {
    case 0:
        object->stateUpdate = FSi_CloseFileCommand_020a0ec8;
        object->flags |= 0x30;
        break;
    case 1:
        object->flags &= ~0x20;
        object->stateUpdate = FieldObject_AdvanceToAnimEnd_020a0ecc;
        object->flags &= ~0x10;
        QuadTree_RemoveObject_02033c60(func_02036230()->quadTree->tree, object->objectClass + 0x11c);
        SetObjectAnimTrack_0207f8d0(object, 1);
        object->frame = 0;
        break;
    case 2:
        object->flags &= ~0x20;
        object->stateUpdate = FSi_CloseFileCommand_020a0ef8;
        object->flags &= ~0x10;
        break;
    }
}
