#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventGroup {
    u8 unknown_00[4];
    u8 pending;
    u8 unknown_05[0x17];
} EventGroup;

typedef struct SceneWork {
    u8 unknown_00[0x1f];
    u8 objectGroup;
    u8 objectIndex;
    u8 unknown_21[0x0f];
    s16 targetEventId;
    u8 unknown_32[0x11];
    s8 eventArea;
    u8 unknown_44[0x0c];
    EventGroup *groups;
} SceneWork;

typedef struct EventActor {
    u8 unknown_00[0x38];
    VecFx32 position;
} EventActor;

typedef struct EffectParams {
    VecFx32 *position;
    VecFx32 *offset;
    fx32 scale;
    u16 enable;
    u16 priority;
    int flags;
    u8 unknown_14[0x4c];
} EffectParams;

typedef struct EffectResult {
    u8 unknown_00[0x2c];
    fx32 scale;
} EffectResult;

extern SceneWork *data_ov035_020bc4e0;
extern const VecFx32 data_ov035_020bc3e0;
extern int func_ov001_020645c8(int flagId);
extern void func_ov001_020645dc(int flagId);
extern EventActor *func_ov001_02087224(int area, int eventId);
extern void *func_ov001_0207f038(u32 group, u32 index);
extern int func_02036230(void);
extern EffectResult *func_020351b8(int handle, EffectParams *params);
extern void addScaledVector_020301ac(fx32 scale, const VecFx32 *scaledVector, const VecFx32 *baseVector, VecFx32 *resultVector);
extern void FieldObject_CallHook24_0207f800(void *object, VecFx32 *position);
extern void FieldObject_SetEnabled_0207f6f4(void *object, BOOL enabled);
extern void func_ov001_02078680(void);

void OnGroupEventFinished_020bb1ac(int group, int eventId) {
    SceneWork *work = data_ov035_020bc4e0;
    EventActor *actor;
    void *object;
    EffectParams params;
    VecFx32 result;
    VecFx32 offset;
    VecFx32 position;

    work->groups[group].pending--;
    if (func_ov001_020645c8(0x3702) == 0 && eventId == work->targetEventId) {
        actor = func_ov001_02087224(work->eventArea, eventId);
        object = func_ov001_0207f038(work->objectGroup, work->objectIndex);
        offset = data_ov035_020bc3e0;
        position = actor->position;
        position.y += 0x800;
        params.scale = 0x1000;
        params.position = &position;
        params.offset = &offset;
        params.enable = 1;
        params.priority = 0xf;
        params.flags = 0;
        addScaledVector_020301ac(func_020351b8(func_02036230(), &params)->scale, &offset, &position, &result);
        FieldObject_CallHook24_0207f800(object, &result);
        FieldObject_SetEnabled_0207f6f4(object, TRUE);
        func_ov001_020645dc(0x3702);
    }
    func_ov001_02078680();
}
