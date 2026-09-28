#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraParams {
    u32 unk_00;
    VecFx32 origin;
    fx32 unk_10;
    fx32 unk_14;
    fx32 unk_18;
    u32 unk_1C;
    fx32 unk_20;
    fx32 unk_24;
    u8 pad_28[4];
    u8 body[1];
} CameraParams;

typedef struct MoviePlayerCtx {
    u8 pad_00[0x30];
    CameraParams *cameraParams;
    u8 *cameraBody;
    u8 pad_38[0x18];
    s32 unk_50;
} MoviePlayerCtx;

extern MoviePlayerCtx *g_moviePlayerCtx_020bd000;
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern u32 func_ov001_020636e4(void);
extern int findSharedResourceByName_0202cd8c(unsigned char *table, void *name);
extern CameraParams *func_0202c478(u32 fileId, u32 param2, u32 param3, u32 param4);
extern void func_ov030_020bb2cc(VecFx32 *origin, fx32 a, fx32 b, fx32 c, s32 flag, fx32 d);
extern void func_ov042_020bd660(u32 flags);
extern void func_ov042_020bd5e0(fx32 value);
extern void func_ov030_020bb374(u8 value);

void LoadCameraParams_020bb390(void *name)
{
    u32 archiveHandle;
    int entryIndex;
    u32 archiveBits;
    CameraParams *params;

    if (g_moviePlayerCtx_020bd000->cameraParams != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(g_moviePlayerCtx_020bd000->cameraParams);
    }
    archiveHandle = func_ov001_020636e4();
    entryIndex = findSharedResourceByName_0202cd8c((unsigned char *)func_ov001_020636e4(), name);
    archiveBits = ((archiveHandle + 0x8000) & 0xfffffc) << 7 | 0x80000000;
    g_moviePlayerCtx_020bd000->cameraParams =
        func_0202c478((entryIndex & 0x1ff) | archiveBits, 2, 0xfffffc, archiveBits);
    g_moviePlayerCtx_020bd000->cameraBody = g_moviePlayerCtx_020bd000->cameraParams->body;
    params = g_moviePlayerCtx_020bd000->cameraParams;
    func_ov030_020bb2cc(&params->origin, params->unk_10, params->unk_14, params->unk_18, 0,
                        params->unk_20);
    func_ov042_020bd660(g_moviePlayerCtx_020bd000->cameraParams->unk_1C);
    func_ov042_020bd5e0(g_moviePlayerCtx_020bd000->cameraParams->unk_24);
    g_moviePlayerCtx_020bd000->unk_50 = -1;
    func_ov030_020bb374(1);
}
