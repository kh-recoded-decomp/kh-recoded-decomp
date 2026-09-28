#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nnsys/g2d.h"

extern const void *func_02014fd8(NNSG2dCellAnimation *pCellAnim);
extern const NNSG2dCellData *G2D_GetCellByIndex_02014c28(const NNSG2dCellDataBank *pBank, u16 idx);
extern void NNSi_G2dSrtcInitControl_0201564c(NNSG2dSRTControl *pCtrl, NNSG2dSRTControlType type);
extern void NNSi_G2dSrtcSetSRTScale_02015630(NNSG2dSRTControl *pCtrl, fx32 x, fx32 y);
extern void NNSi_G2dSrtcSetSRTRotZ_02015614(NNSG2dSRTControl *pCtrl, u16 rotZ);
extern void G2D_SetTranslation_020155f4(NNSG2dSRTControl *pCtrl, s16 x, s16 y);
extern void G2D_RequestCellTransfer_02015b78(u32 handle, u32 srcOffset, u32 szByte);

inline BOOL CellAnimVramTransferHandleValid(const NNSG2dCellAnimation *pCellAnim) {
    return *(const volatile u32 *)&pCellAnim->cellTransferStateHandle != 0xffffffff;
}

/* adapted CC0 shared C */
void TickCellAnimation_02015684(NNSG2dCellAnimation *pCellAnim) {
    if (pCellAnim->animCtrl.pActiveCurrent->frames == 0) {
        return;
    }

    const NNSG2dAnimDataSRT *pAnimResult = (const NNSG2dAnimDataSRT *)func_02014fd8(pCellAnim);
    const NNSG2dCellDataBank *pCellDataBank = pCellAnim->pCellDataBank;
    pCellAnim->pCurrentCell = G2D_GetCellByIndex_02014c28(pCellDataBank, pAnimResult->index);

    u32 elemType = pCellAnim->animCtrl.pAnimSequence->animType & 0xff;
    NNSi_G2dSrtcInitControl_0201564c(&pCellAnim->srtCtrl, NNS_G2D_SRTCONTROLTYPE_SRT);

    if (elemType != 0) {
        if (elemType == 2) {
            const NNSG2dAnimDataT *pAnimT = (const NNSG2dAnimDataT *)pAnimResult;
            G2D_SetTranslation_020155f4(&pCellAnim->srtCtrl, pAnimT->px, pAnimT->py);
        } else {
            NNSi_G2dSrtcSetSRTScale_02015630(&pCellAnim->srtCtrl, pAnimResult->sx, pAnimResult->sy);
            NNSi_G2dSrtcSetSRTRotZ_02015614(&pCellAnim->srtCtrl, pAnimResult->rotZ);
            G2D_SetTranslation_020155f4(&pCellAnim->srtCtrl, pAnimResult->px, pAnimResult->py);
        }
    }

    NNSG2dVramTransferData *pVramTransferData = *(NNSG2dVramTransferData *volatile const *)&pCellDataBank->pVramTransferData;
    BOOL hasTransferData = (BOOL)(pVramTransferData != NULL);
    BOOL hasTransferDataOk = hasTransferData != 0;
    if (!hasTransferDataOk) {
        return;
    }
    if (!CellAnimVramTransferHandleValid(pCellAnim)) {
        return;
    }

    const NNSG2dCellVramTransferData *pTransfer = &pVramTransferData->pCellTransferDataArray[pAnimResult->index];
    G2D_RequestCellTransfer_02015b78(pCellAnim->cellTransferStateHandle, pTransfer->srcDataOffset, pTransfer->szByte);
}
