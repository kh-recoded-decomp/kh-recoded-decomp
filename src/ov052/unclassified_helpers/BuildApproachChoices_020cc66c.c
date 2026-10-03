#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CrowdNode {
    struct CrowdNode *next;
} CrowdNode;

typedef struct {
    u8 pad_00[8];
    VecFx32 position;
    u8 pad_14[0x24 - 0x14];
} EventTargetInfo;

typedef struct ChoiceActor ChoiceActor;

struct ChoiceActor {
    u8 pad_000[0x1dc];
    int state;
    u8 pad_1e0[0x22c - 0x1e0];
    int (*getState)(ChoiceActor *actor);
    u8 pad_230[0x1048 - 0x230];
    u8 waitTarget[4];
};

extern VecFx32 *GetWaitTargetPosition_0206c3f4(void *target);
extern VecFx32 *func_ov052_020ceb54(ChoiceActor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern CrowdNode *func_ov001_0208723c(void);
extern VecFx32 *func_ov001_020863f4(CrowdNode *node);
extern s32 func_ov001_02087928(void);
extern s32 func_ov001_02087944(s32 id);
extern int IsStageEventReady_02087c78(u32 id);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out);

void BuildApproachChoices_020cc66c(ChoiceActor *actor, BOOL above, int *choices)
{
    fx32 distance;
    BOOL crowded = FALSE;
    int count = 0;
    VecFx32 *target = GetWaitTargetPosition_0206c3f4(actor->waitTarget);
    VecFx32 *self = func_ov052_020ceb54(actor);
    VecFx32 diff;
    EventTargetInfo info;
    fx32 height;
    int i;
    int state;
    BOOL near;

    VEC_Subtract_01ff9e3c(target, self, &diff);
    diff.y = 0;
    distance = VEC_Mag_01ff9f28(&diff);
    for (i = 0; i < 6; i++) {
        choices[i] = -1;
    }
    if (distance < 0x6000) {
        if (!above) {
            if (target->y - self->y > 0x2000) {
                if (actor->getState != NULL) {
                    state = actor->getState(actor);
                } else {
                    state = actor->state;
                }
                if (state != 6) {
                    choices[0] = 4;
                    return;
                }
            }
        } else if (self->y - target->y > 0x2000) {
            choices[0] = 5;
            count++;
        }
    }
    near = FALSE;
    height = target->y - self->y;
    if (height < 0) {
        height = -height;
    }
    if (func_01ffa0f4(self, target) < 0x3000 && height < 0x1800) {
        near = TRUE;
    }
    if (near) {
        int nearby = 0;
        CrowdNode *node;
        s32 event;

        for (node = func_ov001_0208723c(); node != NULL; node = node->next) {
            VecFx32 *position = func_ov001_020863f4(node);
            if (position != NULL) {
                height = position->y - self->y;
                if (height < 0) {
                    height = -height;
                }
                if (func_01ffa0f4(self, position) < 0x3000 && height < 0x1800) {
                    nearby++;
                }
            }
        }
        for (event = func_ov001_02087928(); event != 0; event = func_ov001_02087944(event)) {
            if (IsStageEventReady_02087c78(event) && GetStageEventTargetInfo_02087960(event, &info)) {
                height = info.position.y - self->y;
                if (height < 0) {
                    height = -height;
                }
                if (func_01ffa0f4(self, &info.position) < 0x3000 && height < 0x1800) {
                    nearby++;
                }
            }
        }
        if (nearby >= 2) {
            choices[count] = 3;
            count++;
            crowded = TRUE;
        }
    }
    if (distance <= 0x2000) {
        choices[count] = 0;
        count++;
        if (!crowded) {
            choices[count] = 3;
            count++;
        }
        choices[count] = 1;
        count++;
        choices[count] = 2;
        count++;
    } else if (distance > 0x2000 && distance < 0x5000) {
        choices[count] = 1;
        count++;
        choices[count] = 0;
        count++;
        if (!crowded) {
            choices[count] = 3;
            count++;
        }
        choices[count] = 2;
        count++;
    } else if (distance >= 0x5000) {
        choices[count] = 2;
        count++;
        choices[count] = 1;
        count++;
        choices[count] = 0;
        count++;
        if (!crowded) {
            choices[count] = 3;
            count++;
        }
    }
}
