#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 minX, minY, minZ;
    fx32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct {
    Sphere *shape;
    Box bounds;
    s32 flags;
    VecFx32 delta;
    Box swept;
} ShapeQuery;

typedef struct {
    u8 pad_00[0x18];
} QueryCursor;

typedef struct {
    u8 pad_00[8];
    VecFx32 position;
    u8 pad_14[0x10];
} TargetInfo;

typedef struct {
    VecFx32 offset;
    u8 pad_0c[0x1c];
    u16 flags;
    u8 pad_2a[4];
    u16 player;
    u8 pad_30[4];
    VecFx32 origin;
    u8 pad_40[8];
} HitEvent;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 hidden;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_0c8[0x224 - 0xc8];
    VecFx32 *(*getPosition)(Actor *actor);
    u8 pad_228[0x760 - 0x228];
    s32 frame;
    u8 pad_764[0x9b4 - 0x764];
    u8 player;
};

extern s16 data_0205356c[];
extern const VecFx32 data_02053438;
extern int GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern void RotateOffsetAroundY_020a9160(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void func_0203ad14(ShapeQuery *query, Sphere *shape, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void func_ov001_02087884(void);
extern s32 func_ov001_0208789c(ShapeQuery *query, QueryCursor *cursor, u16 *outResult);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, TargetInfo *out);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void func_01ff8830(void *dst, int value, int size);
extern int DispatchStageEventArg_020878d4(u32 id, HitEvent *event);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern fx32 nextRandom12_0202aa58(void);
extern fx32 FixedPointMultiply12_02006450(fx32 a, fx32 b);
extern int func_ov001_0206db8c(int index);

void EmitSweepHitEvents_020d8350(Actor *actor)
{
    ShapeQuery query;
    HitEvent event;
    ShapeQuery temp;
    QueryCursor cursor;
    Sphere sphere;
    VecFx32 offset;
    TargetInfo info;
    VecFx32 dir;
    MarkerRequest request;
    VecFx32 pos;
    u16 result;
    int angle;
    s32 id;
    int index;
    VecFx32 *origin;

    if (actor->frame < 0x1f000 || actor->frame >= 0x34000) {
        return;
    }
    angle = (u16)(GetLinkedAngleOffset_020ceb7c(actor) - 0x8000);
    offset.x = 0;
    offset.y = 0;
    offset.z = 0x800;
    if (actor->getPosition != NULL) {
        origin = actor->getPosition(actor);
    } else {
        origin = &actor->position;
    }
    RotateOffsetAroundY_020a9160(&offset, origin, angle, &offset);
    func_0203ad14(&temp, &sphere, &offset, 0x1800);
    temp.delta = data_02053438;
    OffsetBoxByDelta_0203ac70(&temp.bounds, &temp.swept, &temp.delta);
    query = temp;
    func_ov001_02087884();
    do {
        id = func_ov001_0208789c(&query, &cursor, &result);
        if (id == 0) {
            return;
        }
        if (!GetStageEventTargetInfo_02087960(id, &info)) {
            continue;
        }
        dir.z = 0;
        dir.y = 0;
        dir.x = 0;
        index = (u16)GetLinkedAngleOffset_020ceb7c(actor) >> 4;
        dir.x = -data_0205356c[index];
        dir.z = -data_0205356c[(0x400 - index) & 0xfff];
        ScaleVecFx32_01ffafb4(0x1000, &dir, &dir);
        func_01ff8830(&event, 0, sizeof(HitEvent));
        event.player = actor->player;
        event.origin = *func_ov052_020ceb54(actor);
        event.offset = dir;
        event.flags |= 0x100;
        DispatchStageEventArg_020878d4(id, &event);
        pos = info.position;
        func_ov021_020a8ab4(&request);
        request.id = actor->player;
        request.layer = 0;
        pos.x += FixedPointMultiply12_02006450(nextRandom12_0202aa58() - 0x800, 0x4cd);
        pos.y += FixedPointMultiply12_02006450(nextRandom12_0202aa58() - 0x800, 0x4cd);
        pos.z += FixedPointMultiply12_02006450(nextRandom12_0202aa58() - 0x800, 0x4cd);
        request.position = pos;
        request.soundId = 0;
        request.delay = 0x21;
        request.hidden = 0;
        func_ov021_020a8ca0(&request, func_ov001_0206db8c(4));
    } while (id != 0);
}
