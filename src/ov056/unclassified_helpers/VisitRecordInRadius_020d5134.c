#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    BOOL (*filter)(s32 recordId, void *userData);
    BOOL (*visitor)(s32 recordId, VecFx32 *position, void *userData);
    VecFx32 *center;
    fx32 radius;
    void *userData;
} RecordSearchContext;

extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL VisitRecordInRadius_020d5134(s32 recordId, VecFx32 *position, RecordSearchContext *context)
{
    if (func_01ffa0f4(position, context->center) > context->radius) {
        return FALSE;
    }
    if (context->visitor != NULL) {
        return context->visitor(recordId, position, context->userData);
    }
    return FALSE;
}
