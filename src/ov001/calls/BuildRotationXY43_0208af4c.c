#include "nitro/fx.h"

extern const s16 gSinFx12Table_0205356c[];
extern void MTX_Identity43__01ff9480(MtxFx43 *matrix);
extern void MTX_RotX43__01ff9510(MtxFx43 *matrix, fx32 sine, fx32 cosine);
extern void MTX_RotY43__01ff9530(MtxFx43 *matrix, fx32 sine, fx32 cosine);
extern void MTX_Concat43_01ff98c0(const MtxFx43 *a, const MtxFx43 *b, MtxFx43 *result);

/* Event-camera angles wrap to one unsigned 16-bit turn. */
void BuildRotationXY43_0208af4c(MtxFx43 *matrix, int xAngle, int yAngle)
{
    MtxFx43 rotation;

    xAngle = (u16)xAngle;
    yAngle = (u16)yAngle;
    MTX_Identity43__01ff9480(matrix);
    MTX_Identity43__01ff9480(&rotation);
    MTX_RotX43__01ff9510(&rotation, gSinFx12Table_0205356c[xAngle >> 4],
               gSinFx12Table_0205356c[(0x400 - (xAngle >> 4)) & 0xfff]);
    MTX_Concat43_01ff98c0(matrix, &rotation, matrix);
    MTX_Identity43__01ff9480(&rotation);
    MTX_RotY43__01ff9530(&rotation, gSinFx12Table_0205356c[yAngle >> 4],
               gSinFx12Table_0205356c[(0x400 - (yAngle >> 4)) & 0xfff]);
    MTX_Concat43_01ff98c0(matrix, &rotation, matrix);
}
