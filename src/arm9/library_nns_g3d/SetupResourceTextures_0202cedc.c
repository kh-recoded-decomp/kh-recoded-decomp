#include "nitro/types.h"
#include "nnsys/g3d.h"

#define SIGNATURE_NSBMD 0x30444d42

typedef NNSGfdPlttKey (*PlttVramAllocFunc)(u32 size, BOOL is4Pltt, u32 fromLow);
typedef int (*PlttVramFreeFunc)(NNSGfdPlttKey key);

extern BOOL g_textureSetupEnabled_02056014;
extern NNSGfdFuncAllocTexVram data_02055c4c;
extern NNSGfdFuncFreeTexVram data_02055c50;
extern PlttVramAllocFunc data_02055c54;
extern PlttVramFreeFunc data_02055c58;

extern NNSG3dResTex *FindTextureResourceBlock_0201ac70(void *file);
extern u32 GetTextureImageBytes_020188cc(const NNSG3dResTex *tex);
extern u32 GetCompressedTextureBytes_020188e0(const NNSG3dResTex *tex);
extern u32 GetPaletteBytes_02018964(const NNSG3dResTex *tex);
extern void ReleaseTextureResourceKeys_020188f4(NNSG3dResTex *tex, NNSGfdTexKey texKey, NNSGfdTexKey tex4x4Key);
extern void func_02018978(NNSG3dResTex *tex, NNSGfdPlttKey plttKey);
extern void Tex_LoadVram_0202d14c(NNSG3dResTex *tex);
extern void func_0202d204(NNSG3dResTex *tex);
extern void *NNS_G3dGetMdlSet_0201ac60(void *file);
extern BOOL BindModelSetTexturesAndPalettes_02018f6c(void *mdlSet, const NNSG3dResTex *tex);

BOOL SetupResourceTextures_0202cedc(u32 signature, void *file, NNSG3dResTex *tex)
{
    if (g_textureSetupEnabled_02056014) {
        u32 texSize;
        u32 tex4x4Size;
        u32 plttSize;
        BOOL texOk = TRUE;
        BOOL tex4x4Ok = TRUE;
        BOOL plttOk = TRUE;
        NNSGfdTexKey texKey;
        NNSGfdTexKey tex4x4Key;
        NNSGfdPlttKey plttKey;

        if (tex == NULL) {
            tex = FindTextureResourceBlock_0201ac70(file);
        }
        if (tex != NULL) {
            texSize = GetTextureImageBytes_020188cc(tex);
            tex4x4Size = GetCompressedTextureBytes_020188e0(tex);
            plttSize = GetPaletteBytes_02018964(tex);

            if (texSize > 0) {
                texKey = data_02055c4c(texSize, FALSE, 0);
                if (texKey == 0) {
                    texOk = FALSE;
                }
            } else {
                texKey = 0;
            }

            if (tex4x4Size > 0) {
                tex4x4Key = data_02055c4c(tex4x4Size, TRUE, 0);
                if (tex4x4Key == 0) {
                    tex4x4Ok = FALSE;
                }
            } else {
                tex4x4Key = 0;
            }

            if (plttSize > 0) {
                plttKey = data_02055c54(plttSize, tex->tex4x4Info.flag & 0x8000, 0);
                if (plttKey == 0) {
                    plttOk = FALSE;
                }
            } else {
                plttKey = 0;
            }

            if (!texOk || !tex4x4Ok || !plttOk) {
                data_02055c58(plttKey);
                data_02055c50(tex4x4Key);
                data_02055c50(texKey);
                return FALSE;
            }

            ReleaseTextureResourceKeys_020188f4(tex, texKey, tex4x4Key);
            func_02018978(tex, plttKey);
            Tex_LoadVram_0202d14c(tex);
            func_0202d204(tex);
        }

        if (signature == SIGNATURE_NSBMD) {
            void *mdlSet = NNS_G3dGetMdlSet_0201ac60(file);

            if (tex != NULL) {
                BindModelSetTexturesAndPalettes_02018f6c(mdlSet, tex);
            }
        }
    }
    return TRUE;
}
