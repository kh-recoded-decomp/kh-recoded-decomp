#include "nitro/types.h"
#include "nnsys/g2d.h"

#define NFTR_VERSION_1_2 0x0102

extern void RunResetCallbackAndIdle_02004cf0(void);
extern void relocateFontResource_02018314(NNSG2dBinaryFileHeader *pHeader);
extern NNSG2dBinaryBlockHeader *G2D_FindResourceBlock_02014e00(NNSG2dBinaryFileHeader *pHeader, u32 signature);

static inline BOOL IsBinFileSignatureValid(const NNSG2dBinaryFileHeader *pBinFile, u32 signature)
{
    if (pBinFile != NULL) {
        if (pBinFile->signature == signature) {
            return TRUE;
        }
    }
    return FALSE;
}

static inline BOOL IsBinFileVersionValid(const NNSG2dBinaryFileHeader *pBinFile, u16 version)
{
    if (pBinFile != NULL) {
        if (pBinFile->version >= version) {
            return TRUE;
        }
    }
    return FALSE;
}

static inline BOOL IsBinFileValid(const NNSG2dBinaryFileHeader *pBinFile, u32 signature, u16 version)
{
    if (pBinFile != NULL) {
        return IsBinFileSignatureValid(pBinFile, signature) && IsBinFileVersionValid(pBinFile, version);
    }
    return FALSE;
}

BOOL NNSi_G2dGetUnpackedFont_02018150(void *pNftrFile, NNSG2dFontInformation **ppRes)
{
    BOOL isOldVersion = FALSE;

    if (!IsBinFileValid((NNSG2dBinaryFileHeader *)pNftrFile, NNS_G2D_BINFILE_SIG_FONTDATA, NFTR_VERSION_1_2)) {
        if (!IsBinFileValid((NNSG2dBinaryFileHeader *)pNftrFile, NNS_G2D_BINFILE_SIG_FONTDATA, NNS_G2D_NFTR_VER)) {
            if (!IsBinFileValid((NNSG2dBinaryFileHeader *)pNftrFile, NNS_G2D_BINFILE_SIG_FONTDATA, NNS_G2D_NFTR_PREV_VER)) {
                RunResetCallbackAndIdle_02004cf0();
            }
            isOldVersion = TRUE;
        }
    }

    {
        NNSG2dBinaryFileHeader *pBinFile = (NNSG2dBinaryFileHeader *)pNftrFile;
        NNSG2dBinaryBlockHeader *pBinBlock;

        relocateFontResource_02018314(pBinFile);
        pBinBlock = G2D_FindResourceBlock_02014e00(pBinFile, NNS_G2D_BINBLK_SIG_FINFDATA);

        if (pBinBlock == NULL) {
            *ppRes = NULL;
            return FALSE;
        }

        *ppRes = (NNSG2dFontInformation *)((u8 *)pBinBlock + sizeof(*pBinBlock));
        if (isOldVersion) {
            (*ppRes)->pGlyph->flags = 0;
        }
    }

    return TRUE;
}
