#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Matrix33 {
    fx32 m[3][3];
} Matrix33;

typedef struct SceneNode {
    u16 flags;
    u8 pad_02[0x7e];
    Matrix33 rotation;
} SceneNode;

extern const s16 data_0205356c[];
extern void func_01ff90ec(Matrix33 *mtx);
extern void MTX_RotX33_01ff9220(Matrix33 *mtx, fx32 sinValue, fx32 cosValue);
extern void MTX_RotY33_01ff923c(Matrix33 *mtx, fx32 sinValue, fx32 cosValue);
extern void MTX_Concat33_01ff9270(const Matrix33 *a, const Matrix33 *b, Matrix33 *ab);

void SetNodeRotationXY_0208f34c(SceneNode *node, u32 axes, int angleY, int angleX)
{
    Matrix33 rotateX;
    Matrix33 rotateY;

    func_01ff90ec(&rotateX);
    func_01ff90ec(&rotateY);
    if (axes & 1) {
        MTX_RotX33_01ff9220(&rotateX, data_0205356c[angleX >> 4], data_0205356c[(0x400 - (angleX >> 4)) & 0xfff]);
    }
    if (axes & 2) {
        MTX_RotY33_01ff923c(&rotateY, data_0205356c[angleY >> 4], data_0205356c[(0x400 - (angleY >> 4)) & 0xfff]);
    }
    MTX_Concat33_01ff9270(&rotateX, &rotateY, &node->rotation);
    node->flags &= 0xffdf;
}
