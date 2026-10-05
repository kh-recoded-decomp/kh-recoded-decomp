#include "nitro/types.h"
#include "nitro/fx_types.h"

struct FieldObject;

typedef struct ListNode {
    u8 kind;
    u8 flags;
    u16 arg;
    struct ListNode *next;
} ListNode;

typedef BOOL (*NodeHandler)(void *context, struct FieldObject *obj, u16 arg);

typedef struct FieldDef {
    u8 pad_000[0x188];
    NodeHandler handlers[1];
} FieldDef;

typedef struct FieldObject {
    u8 pad_00[4];
    FieldDef *def;
    u8 pad_08[0x2a];
    u8 slot;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[6];
    s8 state;
    u8 flags : 7;
    u8 moving : 1;
    u8 pad_4c[4];
    s32 unk_50 : 16;
    s32 kind : 12;
    s32 hasTimer : 1;
    s32 : 3;
    VecFx32 prevPosition;
    ListNode *listHead;
    ListNode *listTail;
    fx32 timer;
    s16 parentIndex;
    s16 childIndex;
    u8 context[4];
} FieldObject;

typedef struct ActorBody {
    void *shape;
    s32 box[6];
    s32 shapeKind;
    VecFx32 delta;
    s32 sweptBox[6];
} ActorBody;

typedef struct Actor {
    u8 pad_000[0xa8];
    VecFx32 lastPosition;
    u8 pad_b4[0x58];
    u8 collision[0x24];
    ActorBody body;
} Actor;

extern const VecFx32 data_02053438;

extern u32 func_ov042_020bd6ec(void);
extern fx32 *func_ov042_020bd290(void);
extern fx32 *func_ov042_020bd590(void);
extern void SetFieldObjectHidden_020a3c78(FieldObject *obj, BOOL hidden);
extern void ActorSlot_UnlinkByIndex_02035c28(int index);
extern void CacheEntry_SetActive_02087258(FieldObject *obj, BOOL active);
extern Actor *func_02036240(u32 id);
extern void OffsetBoxByDelta_0203ac70(const void *src, void *dst, const VecFx32 *delta);
extern void SetCollisionObjectPosition_02033f48(void *object, const VecFx32 *position);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void DispatchListHeadCallback_020a4100(FieldObject *obj);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern FieldObject *func_ov001_0208635c(FieldDef *def, int index);
extern int UpdateFieldObjectBreakAnim_020a3554(FieldObject *obj);

static inline void ApplyBodyDelta(ActorBody *body, const VecFx32 *delta)
{
    body->delta = *delta;
    OffsetBoxByDelta_0203ac70(body->box, body->sweptBox, &body->delta);
}

int UpdateMovingFieldObject_020a3610(FieldObject *obj)
{
    FieldDef *def = obj->def;
    Actor *actor;
    FieldObject *child;
    ListNode *node;
    VecFx32 childDelta;
    VecFx32 delta;
    VecFx32 diff;
    s16 index;

    if ((obj->flags & 2) && obj->kind != 2) {
        return 0;
    }
    if (!(func_ov042_020bd6ec() & 1)) {
        fx32 *base = func_ov042_020bd290();
        fx32 *range = func_ov042_020bd590();
        if (obj->position.x - *base < *range * 3) {
            SetFieldObjectHidden_020a3c78(obj, TRUE);
            ActorSlot_UnlinkByIndex_02035c28(obj->slot);
            CacheEntry_SetActive_02087258(obj, FALSE);
            return 0;
        }
    }
    if (obj->flags & 0x20) {
        ApplyBodyDelta(&func_02036240(obj->slot)->body, &data_02053438);
    } else if (obj->parentIndex == -1) {
        actor = func_02036240(obj->slot);
        obj->prevPosition = obj->position;
        SetCollisionObjectPosition_02033f48(actor->collision, &obj->prevPosition);
        if (obj->listHead != NULL) {
            obj->moving = 1;
            if (def->handlers[obj->listHead->kind](obj->context, obj, obj->listHead->arg)) {
                node = obj->listHead;
                obj->listHead = node->next;
                if (!(node->flags & 1)) {
                    if (node->flags & 4) {
                        NNSi_FndFreeFromDefaultHeap_0202a1c4(node);
                    } else if (node->next != NULL && (node->next->flags & 4)) {
                        node->next = NULL;
                    }
                    if (obj->listTail != NULL) {
                        obj->listTail->next = obj->listHead;
                    }
                } else {
                    obj->listTail = node;
                }
                if (obj->listHead != NULL) {
                    DispatchListHeadCallback_020a4100(obj);
                }
            }
        }
        VEC_Subtract_01ff9e3c(&obj->position, &obj->prevPosition, &diff);
        delta = diff;
        *(VecFx32 *)&childDelta = *(VecFx32 *)&diff;
        if (obj->moving) {
            actor->body.delta = delta;
            OffsetBoxByDelta_0203ac70(actor->body.box, actor->body.sweptBox, &actor->body.delta);
        } else {
            ApplyBodyDelta(&actor->body, &data_02053438);
        }
        actor->lastPosition = obj->position;
        for (index = obj->childIndex; index != -1; index = child->childIndex) {
            child = func_ov001_0208635c(obj->def, index);
            child->prevPosition = child->position;
            VEC_Add_01ff9e0c(&child->position, &childDelta, &child->position);
            actor = func_02036240(child->slot);
            if (obj->moving) {
                actor->body.delta = delta;
                OffsetBoxByDelta_0203ac70(actor->body.box, actor->body.sweptBox, &actor->body.delta);
            } else {
                ApplyBodyDelta(&actor->body, &data_02053438);
            }
            SetCollisionObjectPosition_02033f48(actor->collision, &child->prevPosition);
            actor->lastPosition = child->position;
        }
    }
    if (obj->state == 1) {
        return UpdateFieldObjectBreakAnim_020a3554(obj);
    }
    if (obj->hasTimer && !(obj->flags & 8) && obj->timer != -1) {
        obj->timer += 0x1000;
        if (obj->timer >= 0x5000) {
            obj->timer = -1;
        }
    }
    return 0;
}
