#include "nitro/fx.h"

extern const s16 gSinFx12Table[];
extern void MTX_Identity43_(MtxFx43 *matrix);
extern void MTX_RotX43_(MtxFx43 *matrix, fx32 sine, fx32 cosine);
extern void MTX_RotY43_(MtxFx43 *matrix, fx32 sine, fx32 cosine);
extern void MTX_Concat43(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *result);

/* Event-camera angles wrap to one unsigned 16-bit turn. */
void BuildRotationXY43(MtxFx43 *matrix, int xAngle, int yAngle)
{
    MtxFx43 rotation;

    xAngle = (u16)xAngle;
    yAngle = (u16)yAngle;
    MTX_Identity43_(matrix);
    MTX_Identity43_(&rotation);
    MTX_RotX43_(&rotation, gSinFx12Table[xAngle >> 4],
               gSinFx12Table[(0x400 - (xAngle >> 4)) & 0xfff]);
    MTX_Concat43(matrix, &rotation, matrix);
    MTX_Identity43_(&rotation);
    MTX_RotY43_(&rotation, gSinFx12Table[yAngle >> 4],
               gSinFx12Table[(0x400 - (yAngle >> 4)) & 0xfff]);
    MTX_Concat43(matrix, &rotation, matrix);
}
