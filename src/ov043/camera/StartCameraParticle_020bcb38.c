#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

extern u8 *data_ov043_020bd2c0;
extern MtxFx43 data_0205a970;
extern void MTX_Copy43To33_01ff913c(const MtxFx43 *src, MtxFx33 *dst);
extern void InitLaunchedParticle_020afa70(void *particle, const VecFx32 *position, const VecFx32 *launch, int param40, int param44, int param2c);

void StartCameraParticle_020bcb38(const VecFx32 *launch, int param40, int param44, int param2c) {
    MtxFx33 rotation;
    MtxFx33 fetched;
    MTX_Copy43To33_01ff913c(&data_0205a970, &fetched);
    rotation = fetched;
    InitLaunchedParticle_020afa70(data_ov043_020bd2c0 + 0xa8, (const VecFx32 *)rotation.m[2], launch, param40, param44, param2c);
}
