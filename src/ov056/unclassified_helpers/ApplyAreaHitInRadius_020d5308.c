#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef BOOL (*RecordFilter)(s32 recordId, void *userData);
typedef BOOL (*RecordVisitor)(s32 recordId, VecFx32 *position, void *userData);

typedef struct {
    s8 team;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x15];
    u8 unk_25;
    u8 pad_26[6];
} HitParams;

typedef struct {
    u8 pad_00[0x3C];
    s8 team;
} HitOwner;

typedef struct {
    HitParams params;
    HitOwner *owner;
    void *extra;
} AreaHitSearch;

extern void func_ov021_020a8ab4(HitParams *params);
extern BOOL func_ov056_020d518c(s32 recordId, void *userData);
extern BOOL TryAreaHitOnRecord_020d51ec(s32 recordId, VecFx32 *position, void *userData);
extern void ForEachRecordInRadius_020d5164(RecordFilter filter, RecordVisitor visitor, VecFx32 *center, fx32 radius, void *userData);

void ApplyAreaHitInRadius_020d5308(VecFx32 *center, fx32 radius, HitOwner *owner, void *extra)
{
    AreaHitSearch search;

    func_ov021_020a8ab4(&search.params);
    search.params.team = owner->team;
    search.params.unk_25 = 0;
    search.owner = owner;
    search.extra = extra;
    ForEachRecordInRadius_020d5164(func_ov056_020d518c, TryAreaHitOnRecord_020d51ec, center, radius, &search);
}
