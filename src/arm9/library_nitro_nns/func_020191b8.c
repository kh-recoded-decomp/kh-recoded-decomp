/* Queues projection/camera matrices and cached geometry commands, then updates context flags.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_0201574c.c.
 * Original routine: func_0201574c. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned char u8;
typedef unsigned long u32;
typedef long fx32;

typedef struct MtxFx44 {
    fx32 m[4][4];
} MtxFx44;

typedef struct MtxFx43 {
    fx32 m[4][3];
} MtxFx43;

typedef struct NNSG3dGlb {
    u32 cmd0;
    u32 mtxmode_proj;
    MtxFx44 projMtx;
    u32 mtxmode_posvec;
    MtxFx43 cameraMtx;
    u32 cmd1;
    u8 pad80_d4[0x54];
    u32 flag;
} NNSG3dGlb;

extern NNSG3dGlb data_0205a924;
extern void func_01ffa37c(u32 op, const u32 *args, u32 num);

static inline void NNS_G3dGeMtxMode(u32 mode)
{
    func_01ffa37c(0x10, &mode, 1);
}

void FlushGeometryStateVariant_020191b8(void)
{
    func_01ffa37c(0x00001610,
                  (u32 *)&data_0205a924.mtxmode_proj,
                  (sizeof(data_0205a924.mtxmode_proj) + sizeof(data_0205a924.projMtx)) / 4);

    func_01ffa37c(0x19,
                  (u32 *)&data_0205a924.cameraMtx,
                  sizeof(data_0205a924.cameraMtx) / 4);

    NNS_G3dGeMtxMode(2);
    func_01ffa37c(0x15, (u32 *)&data_0205a924.cmd1, 0x16);

    data_0205a924.flag &= ~1u;
    data_0205a924.flag |= 2u;
}
