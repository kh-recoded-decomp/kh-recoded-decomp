#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

inline BOOL NNSi_G2dCellBankHasBR (const NNSG2dCellDataBank * pCellBank)
{
    return (BOOL)(pCellBank->cellBankAttr & 0x1 );
}

void * GetPtrOamArrayHead_02014bc0 (NNSG2dCellDataBank * pCellBank)
{

    if (NNSi_G2dCellBankHasBR(pCellBank)) {
        return (NNSG2dCellDataWithBR *)(pCellBank->pCellDataArrayHead) + pCellBank->numCells;
    } else {
        return pCellBank->pCellDataArrayHead + pCellBank->numCells;
    }
}
