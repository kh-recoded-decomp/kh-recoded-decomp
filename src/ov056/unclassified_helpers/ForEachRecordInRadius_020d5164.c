#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef BOOL (*RecordFilter)(s32 recordId, void *userData);
typedef BOOL (*RecordVisitor)(s32 recordId, VecFx32 *position, void *userData);

typedef struct {
    RecordFilter filter;
    RecordVisitor visitor;
    VecFx32 *center;
    fx32 radius;
    void *userData;
} RecordSearchContext;

extern BOOL InvokeRecordFilter_020d5120(s32 recordId, RecordSearchContext *context);
extern BOOL VisitRecordInRadius_020d5134(s32 recordId, VecFx32 *position, RecordSearchContext *context);
extern void ForEachRecordPosition_020d50b8(void *filter, void *visitor, RecordSearchContext *context);

void ForEachRecordInRadius_020d5164(RecordFilter filter, RecordVisitor visitor, VecFx32 *center, fx32 radius, void *userData)
{
    RecordSearchContext context;

    context.filter = filter;
    context.visitor = visitor;
    context.center = center;
    context.radius = radius;
    context.userData = userData;
    ForEachRecordPosition_020d50b8(InvokeRecordFilter_020d5120, VisitRecordInRadius_020d5134, &context);
}
