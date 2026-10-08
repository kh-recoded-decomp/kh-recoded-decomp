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

extern int func_ov011_020a0ee8(FieldObject *object);
extern int FieldObject_AdvanceToAnimEnd(FieldObject *object);
extern int func_ov011_020a0f18(FieldObject *object);
extern ActorContext *GetActorRegistry(void);
extern void QuadTree_RemoveObject(void *tree, void *object);
extern void SetObjectAnimTrack(FieldObject *object, s8 track);

void FieldObject_SetState(FieldObject *object, int state)
{
    object->state = state;
    switch (state) {
    case 0:
        object->stateUpdate = func_ov011_020a0ee8;
        object->flags |= 0x30;
        break;
    case 1:
        object->flags &= ~0x20;
        object->stateUpdate = FieldObject_AdvanceToAnimEnd;
        object->flags &= ~0x10;
        QuadTree_RemoveObject(GetActorRegistry()->quadTree->tree, object->objectClass + 0x11c);
        SetObjectAnimTrack(object, 1);
        object->frame = 0;
        break;
    case 2:
        object->flags &= ~0x20;
        object->stateUpdate = func_ov011_020a0f18;
        object->flags &= ~0x10;
        break;
    }
}
