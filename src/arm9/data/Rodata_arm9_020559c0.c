#include "nitro/types.h"

extern void AdjustAabbMarginByField_02049c1c(void);
extern void AdjustAabbMargin_02049bf0(void);
extern void ComputePolygonBounds_02049ce4(void);
extern void ShrinkBoundsBySegmentAxis_02049c48(void);
extern void SphereToBounds_020499c4(void);
extern void func_02049a00(void);

void (*const data_020559c0[6])(void) = {
    SphereToBounds_020499c4,
    func_02049a00,
    AdjustAabbMargin_02049bf0,
    AdjustAabbMarginByField_02049c1c,
    ShrinkBoundsBySegmentAxis_02049c48,
    ComputePolygonBounds_02049ce4,
};
