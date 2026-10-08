#define func_01ffe1bc NNS_G3dDraw
#include "nitro/types.h"
#include "nitro/fx_types.h"
typedef struct {
    u8 pad_000[0xb8];
    VecFx32 prmBaseTrans;
} NNSG3dGlbBaseTransView;
extern NNSG3dGlbBaseTransView NNS_G3dGlb;
#define BASE_TRANS NNS_G3dGlb.prmBaseTrans
#define DrawEntryForScreen_020a82ec DrawEntryForScreen
#define func_ov021_020a86b0 PlaceObjectAtEntry
#define SceneNode_Draw_01ffb12c SceneNode_Draw
#define func_ov021_020af5f4 func_ov021_020af614
#define FixedPointMultiply12 FX_Mul
#define camera_commit_explicit_projection_0202a8c4 camera_commit_explicit_projection
#define camera_commit_projection_0202a814 camera_commit_projection
#define MTX_RotY33_01ff923c MTX_RotY33_
#define func_02019188 NNS_G3dGlbFlushP
#define QueueOrSendGeometryCommand_01ffa37c NNS_G3dGeBufferOP_N
#define data_0205356c data_02053580
#define data_0205a9b8 NNS_G3dGlb_prmBaseRot
#define data_0205a9a4 NNS_G3dGlb_prmMatColor0
#include "src/ov021/animation/DrawEntryForScreen_020a82ec.c"
