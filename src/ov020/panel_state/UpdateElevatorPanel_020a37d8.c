#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ElevatorPanel {
    u8 pad_00[0x10];
    u8 shape[0x22];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
    u8 pad_44[4];
    s8 state;
    s8 stackCount;
    s8 delay;
    u8 pad_4b;
    fx32 minY;
    fx32 maxY;
    fx32 deltaY;
    void *link;
} ElevatorPanel;

extern void ApplyBlockLift_020a3398(void *link, fx32 lift);
extern void SetBlockHidden_020a3408(void *link, BOOL hidden);
extern u32 func_ov001_02063838(void);
extern void *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(void *entity, const VecFx32 *position);
extern void BuildCollisionShape_02080834(void *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate, int mode);

int UpdateElevatorPanel_020a37d8(ElevatorPanel *panel)
{
    fx32 oldY;
    void *actor;
    int none = 0;

    panel->deltaY = 0;
    if (panel->link != NULL) {
        ApplyBlockLift_020a3398(panel->link, panel->deltaY);
    }
    if (func_ov001_02063838()) {
        return 0;
    }
    if (panel->state & 0x80) {
        return 0;
    }
    if (!(panel->state & 3)) {
        return 0;
    }
    if (panel->delay > 0) {
        panel->delay--;
        return 0;
    }
    actor = func_02036240(panel->actorId);
    oldY = panel->position.y;
    if (panel->state & 1) {
        panel->position.y = oldY + 0x800;
        if (panel->maxY <= panel->position.y) {
            panel->position.y = panel->maxY;
            panel->state &= ~1;
        }
    } else {
        panel->position.y = oldY - 0x800;
        if (panel->position.y <= panel->minY) {
            panel->position.y = panel->minY;
            panel->state &= ~2;
            panel->state |= 0x80;
            if (panel->link != NULL) {
                SetBlockHidden_020a3408(panel->link, 1);
            }
        }
    }
    Obj_SetPosition_0203569c(actor, &panel->position);
    panel->deltaY = panel->position.y - oldY;
    if (panel->link != NULL) {
        ApplyBlockLift_020a3398(panel->link, panel->deltaY);
    }
    if (panel->deltaY != 0) {
        BuildCollisionShape_02080834(panel->shape, &panel->position, 3, 0x1800, panel->stackCount * 0x1800, 0x1800, none, none, none - 1);
    }
    return 0;
}
