#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

#define reg_G3_COLOR      (*(REGType32v *)0x04000480)
#define reg_G3_TEXCOORD   (*(REGType32v *)0x04000488)
#define reg_G3_VTX_16     (*(REGType32v *)0x0400048c)
#define reg_G3_VTX_XY     (*(REGType32v *)0x04000494)
#define reg_G3_VTX_XZ     (*(REGType32v *)0x04000498)
#define reg_G3_VTX_YZ     (*(REGType32v *)0x0400049c)
#define reg_G3_BEGIN_VTXS (*(REGType32v *)0x04000500)
#define reg_G3_END_VTXS   (*(REGType32v *)0x04000504)

#define GX_FX16PAIR(a, b) ((u32)(((u32)(u16)(a)) | ((u32)(u16)(b) << 16)))
#define GX_BEGIN_QUADS 1

typedef struct ModelDrawObject {
    u8 pad_00[0xa4];
    VecFx32 translation;
} ModelDrawObject;

static inline void G3_Vtx(fx16 x, fx16 y, fx16 z)
{
    reg_G3_VTX_16 = GX_FX16PAIR(x, y);
    reg_G3_VTX_16 = (u32)(u16)z;
}

static inline void G3_VtxXY(fx16 x, fx16 y)
{
    reg_G3_VTX_XY = GX_FX16PAIR(x, y);
}

static inline void G3_VtxXZ(fx16 x, fx16 z)
{
    reg_G3_VTX_XZ = GX_FX16PAIR(x, z);
}

static inline void G3_VtxYZ(fx16 y, fx16 z)
{
    reg_G3_VTX_YZ = GX_FX16PAIR(y, z);
}

static inline void G3_TexCoord(fx16 s, fx16 t)
{
    reg_G3_TEXCOORD = GX_FX16PAIR(s, t);
}

/* Vertex colours of each pair of opposite faces: the positive face's row, then the negative one's. */
extern u16 data_027e0058[2][4];
extern u16 data_027e0068[2][4];
extern u16 data_027e0078[2][4];

extern void SetupModelDrawState(ModelDrawObject *object, fx32 scale, const MtxFx33 *rotation, u32 alpha);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern VecFx32 *func_ov021_020af5d4(void);
extern void TransformVectorByBasis(const VecFx32 *vec, const MtxFx33 *basis, VecFx32 *out);
extern void func_01fff8b0(ModelDrawObject *object, fx32 *width, fx32 *height);
extern void GXi_FlushCommandList(void);

/* The corner colours of the face on `side` (0 = positive, 1 = negative) of a pair. */
static inline const u16 *FaceColors(u16 (*table)[4], int side)
{
    return table[side];
}

/* Draws the faces of a textured unit box that the camera can see: for each axis, the face on the
 * camera's side once the camera is past it. The box stands on the object's position, is scaled by
 * size and turned by the rotation, and each face is one quad spanning the whole texture, going
 * from start to end along its other axis. */
void DrawTexturedBox(ModelDrawObject *object, fx32 size, const MtxFx33 *rotation, u32 alpha)
{
    fx32 half = size >> 1;
    VecFx32 center = object->translation;
    VecFx32 toCamera;
    fx32 width;
    fx32 height;

    SetupModelDrawState(object, size, rotation, alpha);
    if (rotation->_11 == FX32_ONE) {
        center.y += half;
    } else {
        VEC_MultAdd(half, (const VecFx32 *)rotation->m[1], &center, &center);
    }
    VEC_Subtract(func_ov021_020af5d4(), &center, &toCamera);
    if (rotation->_00 != FX32_ONE || rotation->_11 != FX32_ONE || rotation->_22 != FX32_ONE) {
        TransformVectorByBasis(&toCamera, rotation, &toCamera);
    }
    func_01fff8b0(object, &width, &height);
    GXi_FlushCommandList();
    reg_G3_BEGIN_VTXS = GX_BEGIN_QUADS;
    if ((toCamera.x < 0 ? -toCamera.x : toCamera.x) > half) {
        fx32 x = (toCamera.x >= 0 ? 1 : -1) * 0x800;
        int side = x > 0 ? 0 : 1;
        fx32 start = -x;
        fx32 end = start + (x > 0 ? FX32_ONE : -FX32_ONE);

        reg_G3_COLOR = FaceColors(data_027e0058, side)[0];
        G3_TexCoord(0, 0);
        G3_Vtx(x, FX32_ONE, end);
        reg_G3_COLOR = FaceColors(data_027e0058, side)[1];
        G3_TexCoord(0, height >> 8);
        G3_VtxYZ(0, end);
        reg_G3_COLOR = FaceColors(data_027e0058, side)[2];
        G3_TexCoord(width >> 8, height >> 8);
        G3_VtxYZ(0, start);
        reg_G3_COLOR = FaceColors(data_027e0058, side)[3];
        G3_TexCoord(width >> 8, 0);
        G3_VtxYZ(FX32_ONE, start);
    }
    if ((toCamera.y < 0 ? -toCamera.y : toCamera.y) > half) {
        fx32 y = (toCamera.y >= 0 ? 1 : -1) * 0x800;
        int side = y > 0 ? 0 : 1;
        fx32 start = -y;
        fx32 end = start + (y > 0 ? FX32_ONE : -FX32_ONE);

        reg_G3_COLOR = FaceColors(data_027e0068, side)[0];
        G3_TexCoord(0, 0);
        G3_Vtx(start, y + 0x800, -0x800);
        reg_G3_COLOR = FaceColors(data_027e0068, side)[1];
        G3_TexCoord(0, height >> 8);
        G3_VtxXZ(start, 0x800);
        reg_G3_COLOR = FaceColors(data_027e0068, side)[2];
        G3_TexCoord(width >> 8, height >> 8);
        G3_VtxXZ(end, 0x800);
        reg_G3_COLOR = FaceColors(data_027e0068, side)[3];
        G3_TexCoord(width >> 8, 0);
        G3_VtxXZ(end, -0x800);
    }
    if ((toCamera.z < 0 ? -toCamera.z : toCamera.z) > half) {
        fx32 z = (toCamera.z >= 0 ? 1 : -1) * 0x800;
        int side = z > 0 ? 0 : 1;
        fx32 start = -z;
        fx32 end = start + (z > 0 ? FX32_ONE : -FX32_ONE);

        reg_G3_COLOR = FaceColors(data_027e0078, side)[0];
        G3_TexCoord(0, 0);
        G3_Vtx(start, FX32_ONE, z);
        reg_G3_COLOR = FaceColors(data_027e0078, side)[1];
        G3_TexCoord(0, height >> 8);
        G3_VtxXY(start, 0);
        reg_G3_COLOR = FaceColors(data_027e0078, side)[2];
        G3_TexCoord(width >> 8, height >> 8);
        G3_VtxXY(end, 0);
        reg_G3_COLOR = FaceColors(data_027e0078, side)[3];
        G3_TexCoord(width >> 8, 0);
        G3_VtxXY(end, FX32_ONE);
    }
    reg_G3_END_VTXS = 0;
}
