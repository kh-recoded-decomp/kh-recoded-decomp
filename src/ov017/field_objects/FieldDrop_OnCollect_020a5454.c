#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DropObject DropObject;

typedef struct DropModel {
    u8 pad_00[0xA4];
    VecFx32 position;
} DropModel;

typedef struct LinkedObject {
    u8 pad_00[0x54];
    u16 flags;
} LinkedObject;

typedef struct DropEvent {
    u8 pad_00[0x0C];
    u8 kind;
    u8 pad_0D[0x0B];
    int state;
} DropEvent;

struct DropObject {
    u8 pad_00[0x04];
    void *manager;
    u8 pad_08[0x28];
    u16 stateFlags;
    u8 actorId;
    u8 pad_33[0x05];
    VecFx32 position;
    u16 saveGroup;
    u8 saveIndex;
    u8 pad_47;
    DropModel *model;
    union {
        void (*callback)(DropObject *self);
        struct {
            s8 variant;
            s8 index;
        } drop;
    } u;
    u8 active;
    u8 pad_51[0x03];
    u16 flags;
    u8 pad_56[0x04];
    s16 linkIndex;
};

extern int func_ov001_0208764c(void);
extern void AddSessionCounter_02063a80(int index, int amount);
extern void func_0202f4e8(void *target);
extern u8 *func_02036240(int actorId);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern LinkedObject *func_ov001_0208635c(void *manager, int index);
extern void *func_ov017_020a5148(DropObject *self);
extern void *func_ov017_020a5188(DropObject *self);
extern void func_ov017_020a523c(void *target, DropObject *self);
extern void func_ov017_020a5244(void *target, DropObject *self);
extern void DropRequest_InitKind0_020874fc(void *request, int dropIndex, int variant, int saveGroup, int saveIndex);
extern void DropRequest_InitKind1_020874e0(void *request, int dropIndex, int variant, int saveGroup, int saveIndex);
extern void func_ov001_02087518(DropObject *self, void *request);
extern void func_ov001_020665bc(int variant, VecFx32 *position);
extern void func_0204da8c(int channel, int soundId, VecFx32 *position, int flags);

int FieldDrop_OnCollect_020a5454(DropObject *self, DropEvent *event)
{
    u8 request[0x18];
    void *target;

    if (func_ov001_0208764c()) {
        return 0x10;
    }
    if ((self->flags & 2) && event->state != 3) {
        return 0;
    }
    if (event->kind == 0xFF) {
        if (self->flags & 0x200) {
            return 0x10;
        }
    } else {
        AddSessionCounter_02063a80(0x1C, 1);
    }
    self->model->position = self->position;
    func_0202f4e8(self->model);
    self->flags |= 0x20;
    RebindAnimTracks_020809d0(func_02036240(self->actorId) + 4, 1, 0);
    func_0202f4e8(func_02036240(self->actorId) + 4);
    self->flags |= 0x10;
    func_ov001_0208635c(self->manager, self->linkIndex)->flags |= 4;
    target = func_ov017_020a5148(self);
    if (target) {
        func_ov017_020a523c(target, self);
    }
    target = func_ov017_020a5188(self);
    if (target) {
        func_ov017_020a5244(target, self);
    }
    self->stateFlags &= ~0x10;
    self->stateFlags &= ~0x8;
    if (self->flags & 0x100) {
        self->u.callback(self);
    } else if (event->kind != 0xFF && (self->u.drop.index >= 0 || self->u.drop.variant >= 0)) {
        if (self->flags & 0x400) {
            DropRequest_InitKind0_020874fc(request, self->u.drop.index, self->u.drop.variant, self->saveGroup, self->saveIndex);
        } else {
            DropRequest_InitKind1_020874e0(request, self->u.drop.index, self->u.drop.variant, self->saveGroup, self->saveIndex);
        }
        func_ov001_02087518(self, request);
        if (self->u.drop.index >= 0 && self->u.drop.variant >= 0) {
            func_ov001_020665bc(self->u.drop.variant, &self->position);
        }
    }
    self->active = 1;
    func_0204da8c(0, 0x2D, &self->position, 0);
    return 0;
}
