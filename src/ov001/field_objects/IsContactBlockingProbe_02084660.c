#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactRef {
    u32 unk_00;
    int kind;
} ContactRef;

typedef struct ContactBody {
    u32 unk_00;
    VecFx32 normal;
} ContactBody;

typedef struct ContactProbe {
    u32 unk_00;
    const VecFx32 *direction;
} ContactProbe;

extern BOOL IsFacingContactNormal_020349d8(ContactRef *ref, const VecFx32 *direction, ContactProbe *probe);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

BOOL IsContactBlockingProbe_02084660(ContactRef *ref, ContactBody *body, ContactProbe *probe)
{
    if (ref->kind != 4 && !IsFacingContactNormal_020349d8(ref, &body->normal, probe)) {
        return FALSE;
    }
    if (VEC_DotProduct_01ff9e6c(probe->direction, &body->normal) >= 0) {
        return FALSE;
    }
    return TRUE;
}
