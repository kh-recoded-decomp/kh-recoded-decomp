#include "nitro/types.h"
#include "nitro/os.h"
#include "nnsys/g2d.h"

#define offsetof(type, member) ((u32)&(((type *)0)->member))

void NNSi_G2dUnpackUserExCellAttrBank(NNSG2dUserExCellAttrBank * pCellAttrBank);

void UnpackExtendedData_02014bdc (void * pExData)
{
    {
        NNSG2dUserExDataBlock * pBlk = (NNSG2dUserExDataBlock *)pExData;
        NNSG2dUserExCellAttrBank * pCellAttrBank = (NNSG2dUserExCellAttrBank *)(pBlk + 1);

        NNSi_G2dUnpackUserExCellAttrBank(pCellAttrBank);
    }
}
