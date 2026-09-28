typedef unsigned char u8;
typedef unsigned long u32;
typedef long fx32;

typedef struct MtxFx44 {
    fx32 m[4][4];
} MtxFx44;

typedef struct MtxFx43 {
    fx32 m[4][3];
} MtxFx43;

typedef struct MtxFx33 {
    fx32 m[3][3];
} MtxFx33;

typedef struct VecFx32 {
    fx32 x, y, z;
} VecFx32;

typedef struct NNSG3dGlb {
    u32 cmd0;
    u32 mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    u32 cmd1;
    u32 prmMatColor0;
    u32 prmMatColor1;
    u32 prmPolygonAttr;
    u32 prmViewPort;
    u32 cmd4;
    MtxFx33 prmBaseRot;
    VecFx32 prmBaseTrans;
    VecFx32 prmBaseScale;
    u32 prmTexImageParam;
    u32 flag;
} NNSG3dGlb;

extern NNSG3dGlb data_0205a924;
extern void func_01ffa37c(u32 op, const u32 *args, u32 num);

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    func_01ffa37c(0x10, &mode, 1);
}

void FlushGeometryState_02019230(void)
{
    func_01ffa37c(0x00001610,
                  (u32 *)&data_0205a924.mtxmode_proj,
                  (sizeof(data_0205a924.mtxmode_proj) + sizeof(data_0205a924.projMtx)) / 4);

    func_01ffa37c(0x19,
                  (u32 *)&data_0205a924.cameraMtx,
                  sizeof(data_0205a924.cameraMtx) / 4);

    func_01ffa37c(0x00001b19,
                  (u32 *)&data_0205a924.prmBaseRot,
                  (sizeof(data_0205a924.prmBaseRot) +
                   sizeof(data_0205a924.prmBaseTrans) +
                   sizeof(data_0205a924.prmBaseScale)) / 4);

    NNS_G3dGeMtxMode(2);

    func_01ffa37c(data_0205a924.cmd1, (u32 *)&data_0205a924.cmd1 + 1, 4);
    func_01ffa37c(0x15, (u32 *)0, 0);
    func_01ffa37c(0x2a, &data_0205a924.prmTexImageParam, 1);

    data_0205a924.flag |= 1u;
    data_0205a924.flag &= ~2u;
}
