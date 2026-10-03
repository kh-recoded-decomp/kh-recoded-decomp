#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0xc];
    fx32 radius;
    fx32 height;
    u8 flash;
    u8 style;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u32 flags;
    u8 pad_04[8];
    VecFx32 pos;
} HitSource;

typedef struct {
    u8 pad_00[0xc];
    VecFx32 pos;
    u16 reserved0 : 1;
    u16 useEntryPos : 1;
    u8 pad_1a[4];
    s8 effectIndex;
} SlotEntry;

typedef struct {
    u8 pad_0000[0x9b4];
    u8 player;
    u8 pad_09b5[3];
    int kind;
    u8 pad_09bc[0xb58 - 0x9bc];
    int effectBase;
    u8 pad_0b5c[0x1100 - 0xb5c];
    s16 markerIndex;
} Actor;

extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern int nextRandom12_0202aa58(void);
extern int FixedPointMultiply12(int left, int right);

void SpawnHitSparkMarker_020d1494(Actor *actor, HitSource *source, SlotEntry *entry, VecFx32 *target)
{
    MarkerRequest request;
    VecFx32 pos;
    VecFx32 dir;
    VecFx32 anchor;

    func_ov021_020a8ab4(&request);
    if (!(source->flags & 0x10) && actor->markerIndex != -1) {
        request.id = actor->player;
        request.style = 0;
        request.flash = 0;
        request.prevIndex = request.index = -1;
        if (!entry->useEntryPos) {
            pos = source->pos;
        } else {
            pos = entry->pos;
        }
        if (source->flags & 1) {
            anchor = *func_ov052_020ceb54(actor);
            anchor.y = target->y;
            VEC_Subtract_01ff9e3c(target, &anchor, &dir);
            func_01ffaff4(&dir, &dir);
            VEC_MultAdd_01ffa09c(0x900, &dir, &anchor, &dir);
            dir.y = target->y;
            request.pos = dir;
            request.prevIndex = actor->effectBase;
            request.index = 6;
            func_ov021_020a8ca0(&request, func_ov001_0206db8c(2));
            return;
        }
        if (source->flags & 0x20) {
            request.pos = pos;
            request.radius = 0x28000;
            request.height = 0x20000;
            request.style = 3;
            func_ov021_020a8ca0(&request, func_ov001_0206db8c(5));
            return;
        }
        pos.x += FixedPointMultiply12(nextRandom12_0202aa58() - 0x800, 0x4cd);
        pos.y += FixedPointMultiply12(nextRandom12_0202aa58() - 0x800, 0x4cd);
        pos.z += FixedPointMultiply12(nextRandom12_0202aa58() - 0x800, 0x4cd);
        request.prevIndex = actor->effectBase;
        request.index = entry->effectIndex;
        if (source->flags & 2) {
            request.flash = 1;
        }
        request.pos = pos;
        func_ov021_020a8ca0(&request, actor->markerIndex);
        if (source->flags & 4) {
            switch (actor->kind) {
            case 0:
                request.index = 4;
                break;
            case 1:
                request.index = 2;
                break;
            case 2:
                request.index = 2;
                break;
            }
            request.flash = 0;
            func_ov021_020a8ca0(&request, func_ov001_0206db8c(4));
        }
    }
}
